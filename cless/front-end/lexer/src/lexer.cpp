#include "cless/front-end/lexer/lexer.h"

#include <fstream>
#include <limits>

#include "cless/core/print/ansi_escape.h"
#include "cless/front-end/lexer/utils.h"

namespace cless::fend::lexer {
using core::types::Message;
using core::types::PreprocessingToken;
using core::types::Token;

Lexer::Lexer(std::string path) : path_(std::move(path)) {
    std::ifstream file(path_);
    if (not file.is_open()) {
        std::cerr << core::print::Bold << "cless: " << core::print::Red << "error:" << core::print::Reset
                  << " cannot find " << path_ << ": no such file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    source.push_back('\0');
    ptr = &source[0];
    line = 1;
    col = 1;
}

Lexer::Return<core::types::Token> Lexer::next() {
    auto pp_token = nextPreprocessingToken();
    if (pp_token.ret.has_value())
        return {core::types::toToken(pp_token.ret.value()), pp_token.msg};
    return {std::nullopt, pp_token.msg};
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

    std::size_t start_line = line, start_col = col;
    if (auto ident = getIdentifier(); ident.ret.has_value() or ident.msg.size() > 0) {
        if (ident.ret.has_value())
            return {
                PreprocessingToken(ident.ret.value(), path_, start_line, start_col, line, col), std::move(ident.msg)};
        return {std::nullopt, std::move(ident.msg)};
    }
    if (auto punct = getPunctuation(); punct.ret.has_value() or punct.msg.size() > 0) {
        if (punct.ret.has_value())
            return {
                PreprocessingToken(punct.ret.value(), path_, start_line, start_col, line, col), std::move(punct.msg)};
        return {std::nullopt, std::move(punct.msg)};
    }
    if (auto float_const = getFloatingConstant(); float_const.ret.has_value() or float_const.msg.size() > 0) {
        if (float_const.ret.has_value())
            return {
                PreprocessingToken(float_const.ret.value(), path_, start_line, start_col, line, col),
                std::move(float_const.msg)};
        return {std::nullopt, std::move(float_const.msg)};
    }
    if (auto int_const = getIntegerConstant(); int_const.ret.has_value() or int_const.msg.size() > 0) {
        if (int_const.ret.has_value())
            return {
                PreprocessingToken(int_const.ret.value(), path_, start_line, start_col, line, col),
                std::move(int_const.msg)};
        return {std::nullopt, std::move(int_const.msg)};
    }
    if (auto char_const = getCharacterConstant(); char_const.ret.has_value() or char_const.msg.size() > 0) {
        if (char_const.ret.has_value())
            return {
                PreprocessingToken(char_const.ret.value(), path_, start_line, start_col, line, col),
                std::move(char_const.msg)};
        return {std::nullopt, std::move(char_const.msg)};
    }
    if (auto str_lit = getStringLiteral(); str_lit.ret.has_value() or str_lit.msg.size() > 0) {
        if (str_lit.ret.has_value())
            return {
                PreprocessingToken(str_lit.ret.value(), path_, start_line, start_col, line, col),
                std::move(str_lit.msg)};
        return {std::nullopt, std::move(str_lit.msg)};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::HeaderName> Lexer::getHeaderName() {
    auto start = tell();
    if (*ptr == '<') {
        std::string name;
        adv();
        while (*ptr != '>') {
            if (utils::isEndOfLineChar(*ptr))
                return {std::nullopt, {Message::error(path_, start.line, start.col, "missing closing angle bracket")}};
            name.push_back(*ptr);
            adv();
        }
        adv();
        return {core::types::HeaderName{name, true}, {}};
    } else if (*ptr == '"') {
        std::string name;
        adv();
        while (*ptr != '"') {
            if (utils::isEndOfLineChar(*ptr))
                return {std::nullopt, {Message::error(path_, start.line, start.col, "missing closing double quote")}};
            name.push_back(*ptr);
            adv();
        }
        adv();
        return {core::types::HeaderName{name, false}, {}};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::Identifier> Lexer::getIdentifier() {
    if (utils::isIdentifierStartChar(*ptr)) {
        std::string name;
        name.push_back(*ptr);
        adv();
        while (utils::isIdentifierChar(*ptr)) {
            name.push_back(*ptr);
            adv();
        }
        return {core::types::Identifier{name}, {}};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::IntegerConstant> Lexer::getIntegerConstant() {
    if (std::isdigit(*ptr)) {
        core::types::IntegerBase base = core::types::IntegerBase::Decimal;
        std::string value, suffix_str;

        // parse base
        if (utils::hasBase(*ptr, lookForward())) {
            adv();
            if (utils::isHexBaseChar(*ptr)) {
                base = core::types::IntegerBase::Hexadecimal;
                adv();
            } else {
                base = core::types::IntegerBase::Octal;
            }
        }

        // parse value
        if (base == core::types::IntegerBase::Hexadecimal) {
            while (std::isxdigit(*ptr)) {
                value.push_back(*ptr);
                adv();
            }
        } else {
            while (std::isdigit(*ptr)) {
                if (base == core::types::IntegerBase::Octal and not utils::isOctDigit(*ptr))
                    return {std::nullopt, {Message::error(path_, line, col, "invalid octal integer constant")}};
                value.push_back(*ptr);
                adv();
            }
        }

        // parse suffix
        auto suffix_start = tell();
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            adv();
        }
        auto suffix = core::types::integerSuffixFromStr(suffix_str);
        if (not suffix.has_value())
            return {
                std::nullopt,
                {Message::error(path_, suffix_start.line, suffix_start.col, "invalid integer constant suffix")}};

        return {core::types::IntegerConstant{base, value, suffix.value()}, {}};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::FloatingConstant> Lexer::getFloatingConstant() {
    // C89 only supports decimal floating constant
    auto start = tell();
    if (std::isdigit(*ptr) or (*ptr == '.' and std::isdigit(lookForward()))) {
        bool is_float = false;
        std::string value, suffix_str;

        // parse significand
        if (*ptr == '.')
            is_float = true;
        value.push_back(*ptr);
        adv();
        while (std::isdigit(*ptr)) {
            value.push_back(*ptr);
            adv();
        }
        if (*ptr == '.') {
            if (not is_float) {
                is_float = true;
                value.push_back(*ptr);
                adv();
                while (std::isdigit(*ptr)) {
                    value.push_back(*ptr);
                    adv();
                }
            } else {
                return {std::nullopt, {Message::error(path_, line, col, "invalid floating constant")}};
            }
        }

        // parse exponent
        auto exp_start = tell();
        if (utils::hasExponent(*ptr, lookForward())) {
            is_float = true;
            value.push_back(*ptr);
            adv();
            if (utils::isSignChar(*ptr)) {
                value.push_back(*ptr);
                adv();
            }
            bool has_exponent_digits = false;
            while (std::isdigit(*ptr)) {
                has_exponent_digits = true;
                value.push_back(*ptr);
                adv();
            }
            if (not has_exponent_digits) {
                return {
                    std::nullopt,
                    {Message::error(path_, exp_start.line, exp_start.col, "floating constant has no exponent digits")}};
            }
        }

        if (not is_float) {
            seek(start);
            return {std::nullopt, {}};
        }

        // parse suffix
        auto suffix_start = tell();
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            adv();
        }
        auto suffix = core::types::floatingSuffixFromStr(suffix_str);
        if (not suffix.has_value())
            return {
                std::nullopt,
                {Message::error(path_, suffix_start.line, suffix_start.col, "invalid floating constant suffix")}};

        return {core::types::FloatingConstant{value, suffix.value()}, {}};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::CharacterConstant> Lexer::getCharacterConstant() {
    auto start = tell();
    if (*ptr == '\'') {
        std::string value;
        std::vector<Message> msg;
        adv();
        while (*ptr != '\'') {
            if (*ptr == '\\') {
                auto esc_start = tell();
                value.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    value.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr))
                        return {
                            std::nullopt,
                            {Message::error(path_, line, col, "hex escape sequence has no hexadecimal digits")}};
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "hex escape sequence out of range"));
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "oct escape sequence out of range"));
                } else if (utils::isEndOfLineChar(*ptr)) {
                    return {
                        std::nullopt, {Message::error(path_, start.line, start.col, "missing closing single quote")}};
                } else {
                    msg.push_back(Message::warning(path_, esc_start.line, esc_start.col, "unknown escape sequence"));
                    value.push_back(*ptr);
                    adv();
                }
            } else if (utils::isEndOfLineChar(*ptr)) {
                return {std::nullopt, {Message::error(path_, start.line, start.col, "missing closing single quote")}};
            } else {
                value.push_back(*ptr);
                adv();
            }
        }
        adv();
        return {core::types::CharacterConstant{value}, msg};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::StringLiteral> Lexer::getStringLiteral() {
    auto start = tell();
    if (*ptr == '"') {
        std::string value;
        std::vector<Message> msg;
        adv();
        while (*ptr != '"') {
            if (*ptr == '\\') {
                auto esc_start = tell();
                value.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    value.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr))
                        return {
                            std::nullopt,
                            {Message::error(path_, line, col, "hex escape sequence has no hexadecimal digits")}};
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "hex escape sequence out of range"));
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max())
                        msg.push_back(
                            Message::warning(path_, esc_start.line, esc_start.col, "oct escape sequence out of range"));
                } else if (utils::isEndOfLineChar(*ptr)) {
                    return {
                        std::nullopt, {Message::error(path_, start.line, start.col, "missing closing double quote")}};
                } else {
                    msg.push_back(Message::warning(path_, esc_start.line, esc_start.col, "unknown escape sequence"));
                    value.push_back(*ptr);
                    adv();
                }
            } else if (utils::isEndOfLineChar(*ptr)) {
                return {std::nullopt, {Message::error(path_, start.line, start.col, "missing closing double quote")}};
            } else {
                value.push_back(*ptr);
                adv();
            }
        }
        adv();
        return {core::types::StringLiteral{value}, msg};
    }
    return {std::nullopt, {}};
}

Lexer::Return<core::types::Punctuation> Lexer::getPunctuation() {
    std::string str;
    str.push_back(*ptr);
    if (char c = lookForward(); std::ispunct(c)) {
        str.push_back(c);
        if (char c = lookForward(2); std::ispunct(c))
            str.push_back(c);
    }

    while (not str.empty()) {
        if (auto punct = core::types::punctuationFromStr(str); punct.has_value()) {
            adv(str.size());
            return {punct, {}};
        }
        str.pop_back();
    }
    return {std::nullopt, {}};
}

}  // namespace cless::fend::lexer
