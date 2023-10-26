#include "cless/front-end/lexer/impl.h"

#include <format>
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
static const std::regex integer_constant_dec_re("^[1-9][0-9]*(\\w*)");
static const std::regex integer_constant_oct_re("^0[0-9]*(\\w*)");
static const std::regex integer_constant_hex_re("^0[xX][0-9a-fA-F]+(\\w*)");
static const std::vector<std::string> integer_constant_suffixes = {
    "",   "u",  "U",  "l",   "L",   "ll",  "LL",  "ul",  "uL",  "Ul",  "UL", "lu",
    "lU", "Lu", "LU", "ull", "uLL", "Ull", "ULL", "llu", "LLu", "llU", "LLU"};

static bool isValidIntegerConstantSuffix(std::string_view str) {
    for (const auto &postfix : integer_constant_suffixes)
        if (str == postfix) return true;
    return false;
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

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_dec_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto suffix = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        if (not isValidIntegerConstantSuffix(suffix))
            return {
                Result::error(LexerError{std::format("invalid suffix \"{}\" on integer constant", suffix), suffix}),
                source};
        return {Result::just(Token{TokenType::IntegerConstant, str}), source.substr(match.length())};
    }

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_hex_re)) {
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
    return {Result::error(LexerError{"not implemented", source}), source};
}

LexerReturn characterConstant(std::string_view source) {
    return {Result::error(LexerError{"not implemented", source}), source};
}

LexerReturn stringLiteral(std::string_view source) {
    return {Result::error(LexerError{"not implemented", source}), source};
}

}  // namespace cless::fend::lexer::impl
