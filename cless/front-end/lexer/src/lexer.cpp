#include "cless/front-end/lexer/lexer.h"

#include <fstream>
#include <limits>

#include "cless/core/print/ansi_escape.h"
#include "cless/core/types/exception.h"
#include "cless/front-end/lexer/utils.h"

namespace cless::fend::lexer {
using core::types::Message;
using syntax::token::PreprocessingToken;
using syntax::token::Token;

Lexer::Lexer(std::string path) : path_(std::move(path)) {
    std::ifstream file(path_);
    if (not file.is_open()) {
        std::cerr << core::print::Bold << "cless: " << core::print::Red << "error:" << core::print::Reset
                  << " cannot find " << path_ << ": no such file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (source.back() != '\n')
        source.push_back('\n');
    ptr = &source[0];
    line = 1;
    col = 1;
}

Lexer::Return<Token> Lexer::next() {
    auto pp_token = nextPreprocessingToken();
    if (pp_token.error)
        return {std::nullopt, std::move(pp_token.msg), true};
    if (pp_token.tok.has_value())
        return {syntax::token::toToken(pp_token.tok.value()), pp_token.msg, false};
    return {std::nullopt, pp_token.msg, false};
}

const std::string& Lexer::path() const {
    return path_;
}

void Lexer::adv(std::size_t n) {
    for (std::size_t i = 0; i < n; i++) {
        if (*ptr == '\0')
            break;
        if (*ptr == '\n') {
            line++;
            col = 0;
        }
        if (*(ptr + 1) == '\\' and *(ptr + 2) == '\n') {
            ptr += 2;
            line++;
            col = 0;
        }
        ptr++;
        col++;
    }
}

char Lexer::lookForward(std::size_t n) const {
    const char* p = ptr;
    for (std::size_t i = 0; i < n; i++) {
        if (*(p + 1) == '\0')
            return '\0';
        if (*(p + 1) == '\\' and *(p + 2) == '\n')
            p += 2;
        p++;
    }
    return *p;
}

Lexer::Position Lexer::tell() const {
    return {ptr, line, col};
}

void Lexer::seek(const Position& pos) {
    ptr = pos.ptr;
    line = pos.line;
    col = pos.col;
}

void Lexer::skipWhitespacesAndComments() {
    // skip whitespaces and comments
    while (true) {
        if (std::isspace(*ptr)) {
            adv();
        } else if (*ptr == '/' and lookForward() == '/') {
            adv(2);
            while (not utils::isEndOfLineChar(*ptr))
                adv();
            adv();
        } else if (*ptr == '/' and lookForward() == '*') {
            adv(2);
            while (*ptr != '*' or lookForward() != '/')
                adv();
            adv(2);
        } else {
            break;
        }
    }
}

Lexer::Return<PreprocessingToken> Lexer::nextPreprocessingToken() {
    skipWhitespacesAndComments();

    if (auto ident = getIdentifier(); ident.tok.has_value() or ident.error) {
        if (ident.error)
            return {std::nullopt, std::move(ident.msg), true};
        return {ident.tok.value(), std::move(ident.msg), false};
    }
    if (auto punct = getPunctuation(); punct.tok.has_value() or punct.error) {
        if (punct.error)
            return {std::nullopt, std::move(punct.msg), true};
        return {punct.tok.value(), std::move(punct.msg), false};
    }
    if (auto float_const = getFloatingConstant(); float_const.tok.has_value() or float_const.error) {
        if (float_const.error)
            return {std::nullopt, std::move(float_const.msg), true};
        return {float_const.tok.value(), std::move(float_const.msg), false};
    }
    if (auto int_const = getIntegerConstant(); int_const.tok.has_value() or int_const.error) {
        if (int_const.error)
            return {std::nullopt, std::move(int_const.msg), true};
        return {int_const.tok.value(), std::move(int_const.msg), false};
    }
    if (auto char_const = getCharacterConstant(); char_const.tok.has_value() or char_const.error) {
        if (char_const.error)
            return {std::nullopt, std::move(char_const.msg), true};
        return {char_const.tok.value(), std::move(char_const.msg), false};
    }
    if (auto str_lit = getStringLiteral(); str_lit.tok.has_value() or str_lit.error) {
        if (str_lit.error)
            return {std::nullopt, std::move(str_lit.msg), true};
        return {str_lit.tok.value(), std::move(str_lit.msg), false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getHeaderName() {
    auto start = tell();
    if (*ptr == '<') {
        std::string name;
        adv();
        while (*ptr != '>') {
            if (utils::isEndOfLineChar(*ptr))
                return {
                    std::nullopt,
                    {Message::error(path_, start.line, start.col, "missing closing angle bracket")},
                    true};
            name.push_back(*ptr);
            adv();
        }
        adv();
        auto end = tell();
        return {syntax::token::HeaderName(name, true, path_, start.line, end.line, start.col, end.col), {}, false};
    } else if (*ptr == '"') {
        std::string name;
        adv();
        while (*ptr != '"') {
            if (utils::isEndOfLineChar(*ptr))
                return {
                    std::nullopt, {Message::error(path_, start.line, start.col, "missing closing double quote")}, true};
            name.push_back(*ptr);
            adv();
        }
        adv();
        auto end = tell();
        return {syntax::token::HeaderName(name, false, path_, start.line, end.line, start.col, end.col), {}, false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getIdentifier() {
    auto start = tell();
    if (utils::isIdentifierStartChar(*ptr)) {
        std::string name;
        name.push_back(*ptr);
        adv();
        while (utils::isIdentifierChar(*ptr)) {
            name.push_back(*ptr);
            adv();
        }
        auto end = tell();
        return {syntax::token::Identifier(name, path_, start.line, end.line, start.col, end.col), {}, false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getIntegerConstant() {
    auto start = tell();
    if (std::isdigit(*ptr)) {
        std::string source;
        // parse base
        utils::Base base = utils::Base::Decimal;
        if (utils::hasBase(*ptr, lookForward(), lookForward(2))) {
            source.push_back(*ptr);
            adv();
            if (utils::isHexBaseChar(*ptr)) {
                base = utils::Base::Hexadecimal;
                source.push_back(*ptr);
                adv();
            } else {
                base = utils::Base::Octal;
            }
        }

        // parse value
        std::intmax_t value = 0;
        if (base == utils::Base::Hexadecimal) {
            while (std::isxdigit(*ptr)) {
                value = value * 16 + utils::charToInt(*ptr);
                source.push_back(*ptr);
                adv();
            }
        } else {
            while (std::isdigit(*ptr)) {
                if (base == utils::Base::Octal and not utils::isOctDigit(*ptr))
                    return {std::nullopt, {Message::error(path_, line, col, "invalid digit in octal constant")}, true};
                value = value * (base == utils::Base::Octal ? 8 : 10) + utils::charToInt(*ptr);
                source.push_back(*ptr);
                adv();
            }
        }

        // parse suffix
        std::string suffix_str;
        auto suffix_start = tell();
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            source.push_back(*ptr);
            adv();
        }
        auto suffix = syntax::token::integerSuffixFromStr(suffix_str);
        if (not suffix.has_value())
            return {
                std::nullopt,
                {Message::error(path_, suffix_start.line, suffix_start.col, "invalid integer constant suffix")},
                true};

        auto end = tell();
        return {
            syntax::token::IntegerConstant(
                value, suffix.value(), std::move(source), path_, start.line, end.line, start.col, end.col),
            {},
            false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getFloatingConstant() {
    // C89 only supports decimal floating constant
    auto start = tell();
    if (std::isdigit(*ptr) or (*ptr == '.' and std::isdigit(lookForward()))) {
        bool is_float = false;
        std::string value_str, suffix_str;
        std::string source;

        // parse significand
        if (*ptr == '.')
            is_float = true;
        value_str.push_back(*ptr);
        source.push_back(*ptr);
        adv();
        while (std::isdigit(*ptr)) {
            value_str.push_back(*ptr);
            source.push_back(*ptr);
            adv();
        }
        if (*ptr == '.') {
            if (not is_float) {
                is_float = true;
                value_str.push_back(*ptr);
                source.push_back(*ptr);
                adv();
                while (std::isdigit(*ptr)) {
                    value_str.push_back(*ptr);
                    source.push_back(*ptr);
                    adv();
                }
            } else {
                return {std::nullopt, {Message::error(path_, line, col, "invalid floating constant")}, true};
            }
        }

        // parse exponent
        auto exp_start = tell();
        if (utils::hasExponent(*ptr, lookForward())) {
            is_float = true;
            value_str.push_back(*ptr);
            source.push_back(*ptr);
            adv();
            if (utils::isSignChar(*ptr)) {
                value_str.push_back(*ptr);
                source.push_back(*ptr);
                adv();
            }
            bool has_exponent_digits = false;
            while (std::isdigit(*ptr)) {
                has_exponent_digits = true;
                value_str.push_back(*ptr);
                source.push_back(*ptr);
                adv();
            }
            if (not has_exponent_digits) {
                return {
                    std::nullopt,
                    {Message::error(path_, exp_start.line, exp_start.col, "floating constant has no exponent digits")},
                    true};
            }
        }

        if (not is_float) {
            seek(start);
            return {std::nullopt, {}, false};
        }

        // parse suffix
        auto suffix_start = tell();
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            source.push_back(*ptr);
            adv();
        }
        auto suffix = syntax::token::floatingSuffixFromStr(suffix_str);
        if (not suffix.has_value())
            return {
                std::nullopt,
                {Message::error(path_, suffix_start.line, suffix_start.col, "invalid floating constant suffix")},
                true};

        auto end = tell();
        return {
            syntax::token::FloatingConstant(
                std::stold(value_str),
                suffix.value(),
                std::move(source),
                path_,
                start.line,
                end.line,
                start.col,
                end.col),
            {},
            false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getCharacterConstant() {
    auto start = tell();
    if (*ptr == '\'') {
        std::string value_str;
        std::string source;
        std::vector<Message> msg;

        adv();
        while (*ptr != '\'') {
            if (*ptr == '\\') {
                auto esc_start = tell();
                source.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value_str.push_back(utils::simpleEscape(*ptr));
                    source.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    source.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr))
                        return {
                            std::nullopt,
                            {Message::error(path_, line, col, "hex escape sequence has no hexadecimal digits")},
                            true};
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        source.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max() or hex < std::numeric_limits<char>::min())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "hex escape sequence out of range"));
                    value_str.push_back(static_cast<char>(hex));
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        source.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max() or oct < std::numeric_limits<char>::min())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "oct escape sequence out of range"));
                    value_str.push_back(static_cast<char>(oct));
                } else if (utils::isEndOfLineChar(*ptr)) {
                    return {
                        std::nullopt,
                        {Message::error(path_, start.line, start.col, "missing closing single quote")},
                        true};
                } else {
                    msg.push_back(Message::warning(path_, esc_start.line, esc_start.col, "unknown escape sequence"));
                    value_str.push_back(*ptr);
                    source.push_back(*ptr);
                    adv();
                }
            } else if (utils::isEndOfLineChar(*ptr)) {
                return {
                    std::nullopt, {Message::error(path_, start.line, start.col, "missing closing single quote")}, true};
            } else {
                value_str.push_back(*ptr);
                source.push_back(*ptr);
                adv();
            }
        }
        adv();

        if (value_str.size() == 0)
            return {std::nullopt, {Message::error(path_, start.line, start.col, "empty character constant")}, true};
        if (value_str.size() > 1)
            msg.push_back(Message::warning(path_, start.line, start.col, "multi-character character constant"));

        std::intmax_t value = 0;
        for (char c : value_str)
            value = value * 256 + c;

        auto end = tell();
        return {
            syntax::token::CharacterConstant(value, std::move(source), path_, start.line, end.line, start.col, end.col),
            msg,
            false};
    }
    return {std::nullopt, {}, false};
}

Lexer::Return<PreprocessingToken> Lexer::getStringLiteral() {
    auto start = tell();
    if (*ptr == '"') {
        std::string value;
        std::string source;
        std::vector<Message> msg;

        adv();
        while (*ptr != '"') {
            if (*ptr == '\\') {
                auto esc_start = tell();
                source.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value.push_back(utils::simpleEscape(*ptr));
                    source.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    source.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr))
                        return {
                            std::nullopt,
                            {Message::error(path_, line, col, "hex escape sequence has no hexadecimal digits")},
                            true};
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        source.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max() or hex < std::numeric_limits<char>::min())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "hex escape sequence out of range"));
                    value.push_back(static_cast<char>(hex));
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        source.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max() or oct < std::numeric_limits<char>::min())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "oct escape sequence out of range"));
                    value.push_back(static_cast<char>(oct));
                } else if (utils::isEndOfLineChar(*ptr)) {
                    return {
                        std::nullopt,
                        {Message::error(path_, start.line, start.col, "missing closing single quote")},
                        true};
                } else {
                    msg.push_back(Message::warning(path_, esc_start.line, esc_start.col, "unknown escape sequence"));
                    value.push_back(*ptr);
                    source.push_back(*ptr);
                    adv();
                }
            } else if (utils::isEndOfLineChar(*ptr)) {
                return {
                    std::nullopt, {Message::error(path_, start.line, start.col, "missing closing single quote")}, true};
            } else {
                value.push_back(*ptr);
                source.push_back(*ptr);
                adv();
            }
        }
        adv();

        auto end = tell();
        return {
            syntax::token::StringLiteral(value, std::move(source), path_, start.line, end.line, start.col, end.col),
            msg,
            false};
    }
    return {std::nullopt, {}, false};
}

static PreprocessingToken buildPunctuation(
    syntax::token::PunctuationType type,
    const std::string& file,
    size_t line_start,
    size_t line_end,
    size_t col_start,
    size_t col_end) {
    switch (type) {
        case syntax::token::PunctuationType::DoubleLessThanEqual:
            return syntax::token::DoubleLessThanEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleGreaterThanEqual:
            return syntax::token::DoubleGreaterThanEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Ellipsis:
            return syntax::token::Ellipsis(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Arrow:
            return syntax::token::Arrow(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoublePlus:
            return syntax::token::DoublePlus(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleMinus:
            return syntax::token::DoubleMinus(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleLessThan:
            return syntax::token::DoubleLessThan(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleGreaterThan:
            return syntax::token::DoubleGreaterThan(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::LessThanEqual:
            return syntax::token::LessThanEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::GreaterThanEqual:
            return syntax::token::GreaterThanEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleEqual:
            return syntax::token::DoubleEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::ExclamationEqual:
            return syntax::token::ExclamationEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleAmpersand:
            return syntax::token::DoubleAmpersand(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleVerticalBar:
            return syntax::token::DoubleVerticalBar(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::AsteriskEqual:
            return syntax::token::AsteriskEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::SlashEqual:
            return syntax::token::SlashEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::PercentEqual:
            return syntax::token::PercentEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::PlusEqual:
            return syntax::token::PlusEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::MinusEqual:
            return syntax::token::MinusEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::AmpersandEqual:
            return syntax::token::AmpersandEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::CaretEqual:
            return syntax::token::CaretEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::VerticalBarEqual:
            return syntax::token::VerticalBarEqual(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::DoubleHash:
            return syntax::token::DoubleHash(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::OpenBracket:
            return syntax::token::OpenBracket(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::CloseBracket:
            return syntax::token::CloseBracket(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::OpenParenthesis:
            return syntax::token::OpenParenthesis(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::CloseParenthesis:
            return syntax::token::CloseParenthesis(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::OpenBrace:
            return syntax::token::OpenBrace(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::CloseBrace:
            return syntax::token::CloseBrace(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Dot:
            return syntax::token::Dot(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Ampersand:
            return syntax::token::Ampersand(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Asterisk:
            return syntax::token::Asterisk(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Plus:
            return syntax::token::Plus(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Minus:
            return syntax::token::Minus(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Tilde:
            return syntax::token::Tilde(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Exclamation:
            return syntax::token::Exclamation(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Slash:
            return syntax::token::Slash(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Percent:
            return syntax::token::Percent(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::LessThan:
            return syntax::token::LessThan(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::GreaterThan:
            return syntax::token::GreaterThan(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Caret:
            return syntax::token::Caret(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::VerticalBar:
            return syntax::token::VerticalBar(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Question:
            return syntax::token::Question(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Colon:
            return syntax::token::Colon(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Semicolon:
            return syntax::token::Semicolon(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Equal:
            return syntax::token::Equal(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Comma:
            return syntax::token::Comma(file, line_start, line_end, col_start, col_end);
        case syntax::token::PunctuationType::Hash:
            return syntax::token::Hash(file, line_start, line_end, col_start, col_end);
    }
    throw core::types::Exception("Unknown punctuation type");
}

Lexer::Return<PreprocessingToken> Lexer::getPunctuation() {
    std::string str;
    str.push_back(*ptr);
    if (char c = lookForward(); std::ispunct(c)) {
        str.push_back(c);
        if (char c = lookForward(2); std::ispunct(c))
            str.push_back(c);
    }

    auto start = tell();
    while (not str.empty()) {
        if (auto punct = syntax::token::punctuationTypeFromStr(str); punct.has_value()) {
            adv(str.size());
            auto end = tell();
            return {buildPunctuation(punct.value(), path_, start.line, end.line, start.col, end.col), {}, false};
        }
        str.pop_back();
    }
    return {std::nullopt, {}, false};
}

}  // namespace cless::fend::lexer
