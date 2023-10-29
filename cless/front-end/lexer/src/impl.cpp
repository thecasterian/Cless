#include "cless/front-end/lexer/impl.h"

#include <format>
#include <iostream>
#include <regex>

namespace cless::fend::lexer::impl {
using core::types::MaybeEither;
using core::types::Token;
using core::types::TokenType;
using Result = LexerReturn::Result;

struct TokenTypeString {
    TokenType type;
    std::string str;
};

static const TokenTypeString keywords[] = {
    {TokenType::Auto, "auto"},
    {TokenType::Break, "break"},
    {TokenType::Bool, "bool"},
    {TokenType::Case, "case"},
    {TokenType::Char, "char"},
    {TokenType::Complex, "complex"},
    {TokenType::Const, "const"},
    {TokenType::Continue, "continue"},
    {TokenType::Default, "default"},
    {TokenType::Do, "do"},
    {TokenType::Double, "double"},
    {TokenType::Else, "else"},
    {TokenType::Enum, "enum"},
    {TokenType::Extern, "extern"},
    {TokenType::Float, "float"},
    {TokenType::For, "for"},
    {TokenType::Generic, "generic"},
    {TokenType::Goto, "goto"},
    {TokenType::If, "if"},
    {TokenType::Imaginary, "imaginary"},
    {TokenType::Inline, "inline"},
    {TokenType::Int, "int"},
    {TokenType::Long, "long"},
    {TokenType::Register, "register"},
    {TokenType::Restrict, "restrict"},
    {TokenType::Return, "return"},
    {TokenType::Short, "short"},
    {TokenType::Signed, "signed"},
    {TokenType::Sizeof, "sizeof"},
    {TokenType::Static, "static"},
    {TokenType::StaticAssert, "static_assert"},
    {TokenType::Struct, "struct"},
    {TokenType::Switch, "switch"},
    {TokenType::Typedef, "typedef"},
    {TokenType::Union, "union"},
    {TokenType::Unsigned, "unsigned"},
    {TokenType::Void, "void"},
    {TokenType::Volatile, "volatile"},
    {TokenType::While, "while"},
};

static const TokenTypeString punctuations[] = {
    // 3 characters
    {TokenType::Ellipsis, "..."},
    {TokenType::DoubleLessThanEqual, "<<="},
    {TokenType::DoubleGreaterThanEqual, ">>="},

    // 2 characters
    {TokenType::Arrow, "->"},
    {TokenType::DoublePlus, "++"},
    {TokenType::DoubleMinus, "--"},
    {TokenType::DoubleLessThan, "<<"},
    {TokenType::DoubleGreaterThan, ">>"},
    {TokenType::LessThanOrEqualTo, "<="},
    {TokenType::GreaterThanOrEqualTo, ">="},
    {TokenType::DoubleEqual, "=="},
    {TokenType::ExclamationEqual, "!="},
    {TokenType::DoubleAmpersand, "&&"},
    {TokenType::DoubleVerticalBar, "||"},
    {TokenType::AsteriskEqual, "*="},
    {TokenType::SlashEqual, "/="},
    {TokenType::PercentEqual, "%="},
    {TokenType::PlusEqual, "+="},
    {TokenType::MinusEqual, "-="},
    {TokenType::AmpersandEqual, "&="},
    {TokenType::CaretEqual, "^="},
    {TokenType::VerticalBarEqual, "|="},

    // 1 character
    {TokenType::OpenBracket, "["},
    {TokenType::CloseBracket, "]"},
    {TokenType::OpenParenthesis, "("},
    {TokenType::CloseParenthesis, ")"},
    {TokenType::OpenBrace, "{"},
    {TokenType::CloseBrace, "}"},
    {TokenType::Dot, "."},
    {TokenType::Ampersand, "&"},
    {TokenType::Asterisk, "*"},
    {TokenType::Plus, "+"},
    {TokenType::Minus, "-"},
    {TokenType::Tilde, "~"},
    {TokenType::Exclamation, "!"},
    {TokenType::Slash, "/"},
    {TokenType::Percent, "%"},
    {TokenType::LessThan, "<"},
    {TokenType::GreaterThan, ">"},
    {TokenType::Caret, "^"},
    {TokenType::VerticalBar, "|"},
    {TokenType::Question, "?"},
    {TokenType::Colon, ":"},
    {TokenType::Semicolon, ";"},
    {TokenType::Equal, "="},
    {TokenType::Comma, ","},
};

static const std::regex identifier_re("^[a-zA-Z_$][a-zA-Z0-9_$]*");
static const std::regex integer_constant_dec_hex_re("^[1-9][0-9]*(\\w*)|^0[xX][0-9a-fA-F]+(\\w*)");
static const std::regex integer_constant_oct_re("^0[0-9]*(\\w*)");
static const std::vector<std::string> integer_constant_suffixes = {
    "",   "u",  "U",  "l",   "L",   "ll",  "LL",  "ul",  "uL",  "Ul",  "UL", "lu",
    "lU", "Lu", "LU", "ull", "uLL", "Ull", "ULL", "llu", "LLu", "llU", "LLU"};
static const std::regex floating_constant_re(
    "^(?:[0-9]*\\.[0-9]+|[0-9]+\\.)(?:[eE][+-]?[0-9]+)?(\\w*)|"
    "^[0-9]+[eE][+-]?[0-9]+(\\w*)|"
    "^0[xX](?:[0-9a-fA-F]*\\.[0-9a-fA-F]+|[0-9a-fA-F]+\\.?)[pP][+-]?[0-9]+(\\w*)");
static const std::vector<std::string> floating_constant_suffixes = {"", "f", "F", "l", "L"};
static const std::regex character_constant_re("^'([^'\\\\\\n]|\\\\.)*\\\\?");
static const std::regex string_literal_re("^\"([^\"\\\\\\n]|\\\\.)*\\\\?");

static bool isValidIntegerConstantSuffix(std::string_view str) {
    for (const auto &suffix : integer_constant_suffixes)
        if (str == suffix) return true;
    return false;
}

static bool isValidFloatingConstantSuffix(std::string_view str) {
    for (const auto &suffix : floating_constant_suffixes)
        if (str == suffix) return true;
    return false;
}

static bool isSimpleEscapeSequence(char c) {
    switch (c) {
        case '\'':
        case '"':
        case '?':
        case '\\':
        case 'a':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
            return true;
        default:
            return false;
    }
}

static bool isOctalDigit(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            return true;
        default:
            return false;
    }
}

LexerReturn keyword(std::string_view source) {
    for (auto &&[token_type, token_str] : keywords)
        if (auto str = source.substr(0, token_str.size()); str == token_str)
            return {Result::just(Token{token_type, str}), source.substr(token_str.size())};

    return {Result::nothing(), source};
}

LexerReturn punctuation(std::string_view source) {
    for (auto &&[token_type, token_str] : punctuations)
        if (auto str = source.substr(0, token_str.size()); str == token_str)
            return {Result::just(Token{token_type, str}), source.substr(token_str.size())};

    return {Result::nothing(), source};
}

LexerReturn identifier(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, identifier_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        return {Result::just(Token{TokenType::Identifier, str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn integerConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_dec_hex_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto suffix = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        if (not isValidIntegerConstantSuffix(suffix))
            return {
                Result::error(LexerError{std::format("invalid suffix \"{}\" on integer constant", suffix), suffix}),
                source};
        return {Result::just(Token{TokenType::IntegerConstant, str}), source.substr(match.length())};
    }

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_oct_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto suffix = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        for (auto it = str.begin(); it < suffix.begin(); it++)
            if (*it == '8' or *it == '9')
                return {
                    Result::error(LexerError{
                        std::format("invalid digit \"{}\" in octal constant", *it), std::string_view{it, it + 1}}),
                    source};
        if (not isValidIntegerConstantSuffix(suffix))
            return {
                Result::error(LexerError{std::format("invalid suffix \"{}\" on integer constant", suffix), suffix}),
                source};
        return {Result::just(Token{TokenType::IntegerConstant, str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn floatingConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, floating_constant_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto suffix = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        if (not isValidFloatingConstantSuffix(suffix))
            return {
                Result::error(LexerError{std::format("invalid suffix \"{}\" on floating constant", suffix), suffix}),
                source};
        return {Result::just(Token{TokenType::FloatingConstant, str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn characterConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, character_constant_re)) {
        auto term_quote = source.begin() + match.position() + match.length();
        if (term_quote == source.end() or *term_quote != '\'')
            return {
                Result::error(LexerError{
                    "missing terminating ' character",
                    std::string_view{source.begin() + match.position(), term_quote}}),
                source};

        for (auto it = source.begin() + match.position() + 1; it != term_quote; ++it) {
            if (*it == '\\') {
                ++it;
                if (*it == 'u' or *it == 'U')
                    return {
                        Result::error(LexerError{
                            "universal character names are not supported", std::string_view{it - 1, it + 1}}),
                        source};
                if (not isSimpleEscapeSequence(*it) and not isOctalDigit(*it) and *it != 'x')
                    return {
                        Result::error(LexerError{"unknown escape sequence", std::string_view{it - 1, it + 1}}), source};
                if (*it == 'x') {
                    ++it;
                    if (not isxdigit(*it))
                        return {
                            Result::error(
                                LexerError{"\\x used with no following hex digits", std::string_view{it - 2, it}}),
                            source};
                }
            }
        }

        auto str = std::string_view{source.begin() + match.position(), term_quote + 1};
        return {Result::just(Token{TokenType::CharacterConstant, str}), source.substr(str.size())};
    }

    return {Result::nothing(), source};
}

LexerReturn stringLiteral(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, string_literal_re)) {
        auto term_quote = source.begin() + match.position() + match.length();
        if (term_quote == source.end() or *term_quote != '"')
            return {
                Result::error(LexerError{
                    "missing terminating \" character",
                    std::string_view{source.begin() + match.position(), term_quote}}),
                source};

        for (auto it = source.begin() + match.position() + 1; it != term_quote; ++it) {
            if (*it == '\\') {
                ++it;
                if (*it == 'u' or *it == 'U')
                    return {
                        Result::error(LexerError{
                            "universal character names are not supported", std::string_view{it - 1, it + 1}}),
                        source};
                if (not isSimpleEscapeSequence(*it) and not isOctalDigit(*it) and *it != 'x')
                    return {
                        Result::error(LexerError{"unknown escape sequence", std::string_view{it - 1, it + 1}}), source};
                if (*it == 'x') {
                    ++it;
                    if (not isxdigit(*it))
                        return {
                            Result::error(
                                LexerError{"\\x used with no following hex digits", std::string_view{it - 2, it}}),
                            source};
                }
            }
        }

        auto str = std::string_view{source.begin() + match.position(), term_quote + 1};
        return {Result::just(Token{TokenType::StringLiteral, str}), source.substr(str.size())};
    }

    return {Result::nothing(), source};
}

}  // namespace cless::fend::lexer::impl
