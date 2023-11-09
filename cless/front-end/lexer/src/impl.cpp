#include "cless/front-end/lexer/impl.h"

#include <cctype>
#include <format>
#include <iostream>
#include <regex>

namespace cless::fend::lexer::impl {
using core::types::CharacterConstant;
using core::types::Error;
using core::types::FloatingConstant;
using core::types::Identifier;
using core::types::IntegerConstant;
using core::types::Keyword;
using core::types::KeywordType;
using core::types::Punctuation;
using core::types::PunctuationType;
using core::types::StringLiteral;
using core::types::Token;

static const std::pair<KeywordType, std::string> keywords[] = {
    {KeywordType::Alignas, "alignas"},
    {KeywordType::Alignof, "alignof"},
    {KeywordType::Auto, "auto"},
    {KeywordType::Bool, "bool"},
    {KeywordType::Break, "break"},
    {KeywordType::Case, "case"},
    {KeywordType::Char, "char"},
    {KeywordType::Complex, "complex"},
    {KeywordType::Const, "const"},
    {KeywordType::Continue, "continue"},
    {KeywordType::Default, "default"},
    {KeywordType::Double, "double"},  // double must come before do
    {KeywordType::Do, "do"},
    {KeywordType::Else, "else"},
    {KeywordType::Enum, "enum"},
    {KeywordType::False, "false"},
    {KeywordType::Float, "float"},
    {KeywordType::For, "for"},
    {KeywordType::Generic, "generic"},
    {KeywordType::If, "if"},
    {KeywordType::Imaginary, "imaginary"},
    {KeywordType::Inline, "inline"},
    {KeywordType::Int, "int"},
    {KeywordType::Long, "long"},
    {KeywordType::Nullptr, "nullptr"},
    {KeywordType::Restrict, "restrict"},
    {KeywordType::Return, "return"},
    {KeywordType::Short, "short"},
    {KeywordType::Signed, "signed"},
    {KeywordType::Sizeof, "sizeof"},
    {KeywordType::StaticAssert, "static_assert"},  // static_assert must come before static
    {KeywordType::Static, "static"},
    {KeywordType::Struct, "struct"},
    {KeywordType::Switch, "switch"},
    {KeywordType::True, "true"},
    {KeywordType::Typedef, "typedef"},
    {KeywordType::Typeof, "typeof"},
    {KeywordType::Union, "union"},
    {KeywordType::Unsigned, "unsigned"},
    {KeywordType::Void, "void"},
    {KeywordType::Volatile, "volatile"},
    {KeywordType::While, "while"},
};

static const std::pair<PunctuationType, std::string> punctuations[] = {
    // 3 characters
    {PunctuationType::Ellipsis, "..."},
    {PunctuationType::DoubleLessThanEqual, "<<="},
    {PunctuationType::DoubleGreaterThanEqual, ">>="},

    // 2 characters
    {PunctuationType::Arrow, "->"},
    {PunctuationType::DoublePlus, "++"},
    {PunctuationType::DoubleMinus, "--"},
    {PunctuationType::DoubleLessThan, "<<"},
    {PunctuationType::DoubleGreaterThan, ">>"},
    {PunctuationType::LessThanOrEqualTo, "<="},
    {PunctuationType::GreaterThanOrEqualTo, ">="},
    {PunctuationType::DoubleEqual, "=="},
    {PunctuationType::ExclamationEqual, "!="},
    {PunctuationType::DoubleAmpersand, "&&"},
    {PunctuationType::DoubleVerticalBar, "||"},
    {PunctuationType::AsteriskEqual, "*="},
    {PunctuationType::SlashEqual, "/="},
    {PunctuationType::PercentEqual, "%="},
    {PunctuationType::PlusEqual, "+="},
    {PunctuationType::MinusEqual, "-="},
    {PunctuationType::AmpersandEqual, "&="},
    {PunctuationType::CaretEqual, "^="},
    {PunctuationType::VerticalBarEqual, "|="},

    // 1 character
    {PunctuationType::OpenBracket, "["},
    {PunctuationType::CloseBracket, "]"},
    {PunctuationType::OpenParenthesis, "("},
    {PunctuationType::CloseParenthesis, ")"},
    {PunctuationType::OpenBrace, "{"},
    {PunctuationType::CloseBrace, "}"},
    {PunctuationType::Dot, "."},
    {PunctuationType::Ampersand, "&"},
    {PunctuationType::Asterisk, "*"},
    {PunctuationType::Plus, "+"},
    {PunctuationType::Minus, "-"},
    {PunctuationType::Tilde, "~"},
    {PunctuationType::Exclamation, "!"},
    {PunctuationType::Slash, "/"},
    {PunctuationType::Percent, "%"},
    {PunctuationType::LessThan, "<"},
    {PunctuationType::GreaterThan, ">"},
    {PunctuationType::Caret, "^"},
    {PunctuationType::VerticalBar, "|"},
    {PunctuationType::Question, "?"},
    {PunctuationType::Colon, ":"},
    {PunctuationType::Semicolon, ";"},
    {PunctuationType::Equal, "="},
    {PunctuationType::Comma, ","},
};

static const std::regex identifier_re("^[a-zA-Z_$][a-zA-Z0-9_$]*");
static const std::regex integer_constant_dec_re("^[1-9][0-9]*(\\w*)");
static const std::regex integer_constant_hex_re("^0[xX][0-9a-fA-F]+(\\w*)");
static const std::regex integer_constant_oct_re("^0[0-9]*(\\w*)");
static const std::regex floating_constant_dec_dot_re("^(?:[0-9]*\\.[0-9]+|[0-9]+\\.)(?:[eE][+-]?[0-9]+)?(\\w*)");
static const std::regex floating_constant_dec_no_dot_re("^[0-9]+[eE][+-]?[0-9]+(\\w*)");
static const std::regex floating_constant_hex_re(
    "^0[xX](?:[0-9a-fA-F]*\\.[0-9a-fA-F]+|[0-9a-fA-F]+\\.?)[pP][+-]?[0-9]+(\\w*)");
static const std::regex floating_constant_no_exponent_digits_re(
    "^0[xX](?:[0-9a-fA-F]*\\.[0-9a-fA-F]+|[0-9a-fA-F]+\\.?)p");
static const std::regex floating_constant_no_exponent_re("^0[xX](?:[0-9a-fA-F]*\\.[0-9a-fA-F]+|[0-9a-fA-F]+\\.)");
static const std::regex floating_constant_no_digits_re("^0[xX]\\.");
static const std::regex character_constant_re("^(\\w*)'((?:[^'\\\\\\n]|\\\\.)*)\\\\?");
static const std::regex string_literal_re("^(\\w*)\"((?:[^\"\\\\\\n]|\\\\.)*)\\\\?");

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

LexerReturn keyword(std::string_view input) {
    for (auto &&[keyword_type, keyword_str] : keywords)
        if (auto source = input.substr(0, keyword_str.size()); source == keyword_str)
            return LexerResult{Keyword{keyword_type, source}, input.substr(keyword_str.size())};

    return std::nullopt;
}

LexerReturn punctuation(std::string_view input) {
    for (auto &&[punct_type, punct_str] : punctuations)
        if (auto source = input.substr(0, punct_str.size()); source == punct_str)
            return LexerResult{Punctuation{punct_type, source}, input.substr(punct_str.size())};

    return std::nullopt;
}

LexerReturn identifier(std::string_view input) {
    std::cmatch match;

    if (std::regex_search(input.begin(), input.end(), match, identifier_re)) {
        auto source = std::string_view(input.begin(), size_t(match.length()));
        std::string name(source.begin(), source.end());
        return LexerResult{Identifier{name, source}, input.substr(match.length())};
    }

    return std::nullopt;
}

LexerReturn integerConstant(std::string_view input) {
    std::cmatch match;

    for (auto &re : {integer_constant_dec_re, integer_constant_hex_re})
        if (std::regex_search(input.begin(), input.end(), match, re)) {
            auto source = std::string_view(input.begin(), size_t(match.length()));
            auto value = std::string(
                input.begin(),
                match.length(1) > 0 ? input.begin() + match.position(1) : input.begin() + match.length());
            auto suffix_src = std::string_view(input.begin() + match.position(1), size_t(match.length(1)));
            auto suffix = core::types::integerSuffixFromStr(std::string(suffix_src));
            if (not suffix.has_value())
                return std::unexpected(
                    Error{std::format("invalid suffix \"{}\" on integer constant", suffix_src), suffix_src});
            return LexerResult{IntegerConstant{value, suffix.value(), source}, input.substr(match.length())};
        }

    if (std::regex_search(input.begin(), input.end(), match, integer_constant_oct_re)) {
        auto source = std::string_view{input.begin(), size_t(match.length())};
        auto value = std::string(
            input.begin(), match.length(1) > 0 ? input.begin() + match.position(1) : input.begin() + match.length());
        auto suffix_src = std::string_view{input.begin() + match.position(1), size_t(match.length(1))};
        auto suffix = core::types::integerSuffixFromStr(std::string(suffix_src));
        for (auto it = source.begin(); it < suffix_src.begin(); it++)
            if (*it == '8' or *it == '9')
                return std::unexpected(
                    Error{std::format("invalid digit \"{}\" in octal constant", *it), std::string_view{it, it + 1}});
        if (not suffix.has_value())
            return std::unexpected(
                Error{std::format("invalid suffix \"{}\" on integer constant", suffix_src), suffix_src});
        return LexerResult{IntegerConstant{value, suffix.value(), source}, input.substr(match.length())};
    }

    return std::nullopt;
}

LexerReturn floatingConstant(std::string_view input) {
    std::cmatch match;

    for (auto &re : {floating_constant_dec_dot_re, floating_constant_dec_no_dot_re, floating_constant_hex_re})
        if (std::regex_search(input.begin(), input.end(), match, re)) {
            auto source = std::string_view{input.begin(), size_t(match.length())};
            auto value = std::string(
                input.begin(),
                match.length(1) > 0 ? input.begin() + match.position(1) : input.begin() + match.length());
            auto suffix_src = std::string_view{input.begin() + match.position(1), size_t(match.length(1))};
            auto suffix = core::types::floatingSuffixFromStr(std::string(suffix_src));
            if (not suffix.has_value())
                return std::unexpected(
                    Error{std::format("invalid suffix \"{}\" on floating constant", suffix_src), suffix_src});
            return LexerResult{FloatingConstant{value, suffix.value(), source}, input.substr(match.length())};
        }

    if (std::regex_search(input.begin(), input.end(), match, floating_constant_no_exponent_digits_re))
        return std::unexpected(
            Error{"exponent has no digits", std::string_view{input.begin(), size_t(match.length())}});
    if (std::regex_search(input.begin(), input.end(), match, floating_constant_no_exponent_re))
        return std::unexpected(Error{
            "hexadecimal floating constants require an exponent",
            std::string_view{input.begin(), size_t(match.length())}});
    if (std::regex_search(input.begin(), input.end(), match, floating_constant_no_digits_re)) {
        auto end = input.begin() + match.length();
        if (end == input.end() or not isxdigit(*end))
            return std::unexpected(
                Error{"no digits in hexadecimal floating constant", std::string_view{input.begin(), end}});
    }

    return std::nullopt;
}

static std::optional<Error> validateEscapeSequence(const std::string &value) {
    for (auto it = value.begin(); it != value.end(); ++it) {
        if (*it == '\\') {
            ++it;
            if (*it == 'u' or *it == 'U')
                return Error{"universal character names are not supported", std::string_view{it - 1, it + 1}};
            if (not isSimpleEscapeSequence(*it) and not isOctalDigit(*it) and *it != 'x')
                return Error{"unknown escape sequence", std::string_view{it - 1, it + 1}};
            if (*it == 'x') {
                ++it;
                if (not isxdigit(*it))
                    return Error{"\\x used with no following hex digits", std::string_view{it - 2, it}};
            }
        }
    }

    return std::nullopt;
}

LexerReturn characterConstant(std::string_view input) {
    std::cmatch match;

    if (std::regex_search(input.begin(), input.end(), match, character_constant_re)) {
        auto term_quote_pos = input.begin() + match.length();
        if (term_quote_pos == input.end() or *term_quote_pos != '\'')
            return std::unexpected(
                Error{"missing terminating ' character", std::string_view(input.begin(), term_quote_pos)});
        if (match.length(2) == 0)
            return std::unexpected(Error{"empty character constant", std::string_view(input.begin(), match.length())});

        auto source = std::string_view(input.begin(), term_quote_pos + 1);
        auto value = std::string(input.begin() + match.length(1) + 1, term_quote_pos);
        auto prefix_src = std::string_view{input.begin(), size_t(match.length(1))};
        auto prefix = core::types::encodingPrefixFromStr(std::string(prefix_src));
        if (not prefix.has_value())
            return std::unexpected(
                Error{std::format("invalid encoding prefix \"{}\" on character constant", prefix_src), prefix_src});

        auto valid = validateEscapeSequence(value);
        if (valid.has_value()) return std::unexpected(valid.value());

        return LexerResult{CharacterConstant{value, prefix.value(), source}, input.substr(source.size())};
    }

    return std::nullopt;
}

LexerReturn stringLiteral(std::string_view input) {
    std::cmatch match;

    if (std::regex_search(input.begin(), input.end(), match, string_literal_re)) {
        auto term_quote_pos = input.begin() + match.length();
        if (term_quote_pos == input.end() or *term_quote_pos != '"')
            return std::unexpected(
                Error{"missing terminating \" character", std::string_view{input.begin(), term_quote_pos}});

        auto source = std::string_view{input.begin(), term_quote_pos + 1};
        auto value = std::string(input.begin() + match.length(1) + 1, term_quote_pos);
        auto prefix_src = std::string_view{input.begin(), size_t(match.length(1))};
        auto prefix = core::types::encodingPrefixFromStr(std::string(prefix_src));
        if (not prefix.has_value())
            return std::unexpected(
                Error{std::format("invalid encoding prefix \"{}\" on string literal", prefix_src), prefix_src});

        auto valid = validateEscapeSequence(value);
        if (valid.has_value()) return std::unexpected(valid.value());

        return LexerResult{StringLiteral{value, prefix.value(), {source}}, input.substr(source.size())};
    }

    return std::nullopt;
}

}  // namespace cless::fend::lexer::impl
