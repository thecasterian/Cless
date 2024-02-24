#include "cless/front-end/lexer/lexer.h"

#include <fstream>
#include <limits>

#include "cless/front-end/lexer/utils.h"

namespace cless::fend::lexer {
using core::types::PreprocessingToken;
using core::types::Token;

Lexer::Lexer(std::string path) : path_(std::move(path)) {
    std::ifstream file(path_);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }

    source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    source.push_back('\0');
    ptr = &source[0];
    line = 1;
    col = 1;
}

std::optional<Token> Lexer::next() {
    if (auto pp_token = nextPreprocessingToken(); pp_token.has_value())
        return core::types::toToken(pp_token.value());
    return std::nullopt;
}

const std::string& Lexer::path() const {
    return path_;
}

void Lexer::adv(std::size_t n) {
    for (std::size_t i = 0; i < n; i++) {
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
            while (*ptr != '\n')
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

std::optional<PreprocessingToken> Lexer::nextPreprocessingToken() {
    skipWhitespacesAndComments();

    std::size_t start_line = line, start_col = col;
    if (auto ident = getIdentifier(); ident.has_value())
        return PreprocessingToken(ident.value(), path_, start_line, start_col, line, col);
    if (auto punct = getPunctuation(); punct.has_value())
        return PreprocessingToken(punct.value(), path_, start_line, start_col, line, col);
    if (auto float_const = getFloatingConstant(); float_const.has_value())
        return PreprocessingToken(float_const.value(), path_, start_line, start_col, line, col);
    if (auto int_const = getIntegerConstant(); int_const.has_value())
        return PreprocessingToken(int_const.value(), path_, start_line, start_col, line, col);
    if (auto char_const = getCharacterConstant(); char_const.has_value())
        return PreprocessingToken(char_const.value(), path_, start_line, start_col, line, col);
    if (auto str_lit = getStringLiteral(); str_lit.has_value())
        return PreprocessingToken(str_lit.value(), path_, start_line, start_col, line, col);
    return std::nullopt;
}

std::optional<core::types::HeaderName> Lexer::getHeaderName() {
    if (*ptr == '<') {
        std::string name;
        adv();
        while (*ptr != '>') {
            name.push_back(*ptr);
            adv();
        }
        adv();
        return core::types::HeaderName{name, true};
    } else if (*ptr == '"') {
        std::string name;
        adv();
        while (*ptr != '"') {
            name.push_back(*ptr);
            adv();
        }
        adv();
        return core::types::HeaderName{name, false};
    }
    return std::nullopt;
}

std::optional<core::types::Identifier> Lexer::getIdentifier() {
    if (utils::isIdentifierStartChar(*ptr)) {
        std::string name;
        name.push_back(*ptr);
        adv();
        while (utils::isIdentifierChar(*ptr)) {
            name.push_back(*ptr);
            adv();
        }
        return core::types::Identifier{name};
    }
    return std::nullopt;
}

std::optional<core::types::IntegerConstant> Lexer::getIntegerConstant() {
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
                if (base == core::types::IntegerBase::Octal and not utils::isOctDigit(*ptr)) {
                    // TODO: invalid octal integer constant
                }
                value.push_back(*ptr);
                adv();
            }
        }

        // parse suffix
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            adv();
        }
        auto suffix = core::types::integerSuffixFromStr(suffix_str);
        if (not suffix.has_value()) {
            // TODO: invalid integer suffix
        }

        return core::types::IntegerConstant{base, value, suffix.value()};
    }
    return std::nullopt;
}

std::optional<core::types::FloatingConstant> Lexer::getFloatingConstant() {
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
                // TODO: invalid floating constant
            }
        }

        // parse exponent
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
                // TODO: invalid floating constant
            }
        }
        if (not is_float) {
            seek(start);
            return std::nullopt;
        }

        // parse suffix
        while (utils::isIdentifierChar(*ptr)) {
            suffix_str.push_back(*ptr);
            adv();
        }
        auto suffix = core::types::floatingSuffixFromStr(suffix_str);
        if (not suffix.has_value()) {
            // TODO: invalid floating suffix
        }

        return core::types::FloatingConstant{value, suffix.value()};
    }
    return std::nullopt;
}

std::optional<core::types::CharacterConstant> Lexer::getCharacterConstant() {
    if (*ptr == '\'') {
        std::string value;
        adv();
        while (*ptr != '\'') {
            if (*ptr == '\\') {
                value.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    value.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr)) {
                        // TODO: invalid hexadecimal escape sequence
                    }
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max()) {
                        // TODO: hex escape sequence out of range
                    }
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max()) {
                        // TODO: oct escape sequence out of range
                    }
                } else if (*ptr == '\n') {
                    // TODO: missing closing single quote
                } else {
                    // TODO: unknown escape sequence
                    value.push_back(*ptr);
                    adv();
                }
            } else {
                value.push_back(*ptr);
                adv();
            }
        }
        adv();
        return core::types::CharacterConstant{value};
    }
    return std::nullopt;
}

std::optional<core::types::StringLiteral> Lexer::getStringLiteral() {
    if (*ptr == '"') {
        std::string value;
        adv();
        while (*ptr != '"') {
            if (*ptr == '\\') {
                value.push_back(*ptr);
                adv();
                if (utils::isSimpleEscapeChar(*ptr)) {
                    value.push_back(*ptr);
                    adv();
                } else if (*ptr == 'x') {
                    std::intmax_t hex = 0;
                    value.push_back(*ptr);
                    adv();
                    if (not std::isxdigit(*ptr)) {
                        // TODO: invalid hexadecimal escape sequence
                    }
                    while (std::isxdigit(*ptr)) {
                        hex = hex * 16 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                    }
                    if (hex > std::numeric_limits<char>::max()) {
                        // TODO: hex escape sequence out of range
                    }
                } else if (utils::isOctDigit(*ptr)) {
                    std::intmax_t oct = 0;
                    int count = 0;
                    while (utils::isOctDigit(*ptr) and count < 3) {
                        oct = oct * 8 + utils::charToInt(*ptr);
                        value.push_back(*ptr);
                        adv();
                        count++;
                    }
                    if (oct > std::numeric_limits<char>::max()) {
                        // TODO: oct escape sequence out of range
                    }
                } else if (*ptr == '\n') {
                    // TODO: missing closing single quote
                } else {
                    // TODO: unknown escape sequence
                    value.push_back(*ptr);
                    adv();
                }
            } else {
                value.push_back(*ptr);
                adv();
            }
        }
        adv();
        return core::types::StringLiteral{value};
    }
    return std::nullopt;
}

std::optional<core::types::Punctuation> Lexer::getPunctuation() {
    std::string str;
    str.push_back(*ptr);
    if (char c = lookForward(); c != '\0')
        str.push_back(c);
    if (char c = lookForward(2); c != '\0')
        str.push_back(c);

    while (not str.empty()) {
        if (auto punct = core::types::punctuationFromStr(str); punct.has_value()) {
            adv(str.size());
            return punct;
        }
        str.pop_back();
    }
    return std::nullopt;
}

}  // namespace cless::fend::lexer
