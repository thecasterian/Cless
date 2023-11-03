#include "cless/front-end/lexer/impl.h"

#include <format>
#include <iostream>
#include <regex>

namespace cless::fend::lexer::impl {
using core::types::CharacterConstant;
using core::types::FloatingConstant;
using core::types::Identifier;
using core::types::IntegerConstant;
using core::types::Keyword;
using core::types::KeywordType;
using core::types::MaybeEither;
using core::types::Punctuation;
using core::types::PunctuationType;
using core::types::StringLiteral;
using core::types::Token;
using Result = LexerReturn::Result;

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
    {KeywordType::Do, "do"},
    {KeywordType::Double, "double"},
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
    {KeywordType::Restrict, "restrict"},
    {KeywordType::Return, "return"},
    {KeywordType::Short, "short"},
    {KeywordType::Signed, "signed"},
    {KeywordType::Sizeof, "sizeof"},
    {KeywordType::Static, "static"},
    {KeywordType::StaticAssert, "static_assert"},
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
static const std::regex integer_constant_dec_hex_re("^[1-9][0-9]*(\\w*)|^0[xX][0-9a-fA-F]+(\\w*)");
static const std::regex integer_constant_oct_re("^0[0-9]*(\\w*)");
static const std::regex floating_constant_re(
    "^(?:[0-9]*\\.[0-9]+|[0-9]+\\.)(?:[eE][+-]?[0-9]+)?(\\w*)|"
    "^[0-9]+[eE][+-]?[0-9]+(\\w*)|"
    "^0[xX](?:[0-9a-fA-F]*\\.[0-9a-fA-F]+|[0-9a-fA-F]+\\.?)[pP][+-]?[0-9]+(\\w*)");
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

LexerReturn keyword(std::string_view source) {
    for (auto &&[keyword_type, keyword_str] : keywords)
        if (auto str = source.substr(0, keyword_str.size()); str == keyword_str)
            return {Result::just(Keyword{keyword_type, str}), source.substr(keyword_str.size())};

    return {Result::nothing(), source};
}

LexerReturn punctuation(std::string_view source) {
    for (auto &&[punct_type, punct_str] : punctuations)
        if (auto str = source.substr(0, punct_str.size()); str == punct_str)
            return {Result::just(Punctuation{punct_type, str}), source.substr(punct_str.size())};

    return {Result::nothing(), source};
}

LexerReturn identifier(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, identifier_re)) {
        auto str = std::string_view(source.begin() + match.position(), size_t(match.length()));
        std::string name(str.begin(), str.end());
        return {Result::just(Identifier{name, str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn integerConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_dec_hex_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto value = std::string(source.begin() + match.position(), source.begin() + match.position(1));
        auto suffix_str = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        auto suffix = core::types::integerSuffixFromStr(std::string(suffix_str));
        if (not suffix.has_value())
            return {
                Result::error(
                    LexerError{std::format("invalid suffix \"{}\" on integer constant", suffix_str), suffix_str}),
                source};
        return {Result::just(IntegerConstant{value, suffix.value(), str}), source.substr(match.length())};
    }

    if (std::regex_search(source.begin(), source.end(), match, integer_constant_oct_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto value = std::string(source.begin() + match.position(), source.begin() + match.position(1));
        auto suffix_str = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        auto suffix = core::types::integerSuffixFromStr(std::string(suffix_str));
        for (auto it = str.begin(); it < suffix_str.begin(); it++)
            if (*it == '8' or *it == '9')
                return {
                    Result::error(LexerError{
                        std::format("invalid digit \"{}\" in octal constant", *it), std::string_view{it, it + 1}}),
                    source};
        if (not suffix.has_value())
            return {
                Result::error(
                    LexerError{std::format("invalid suffix \"{}\" on integer constant", suffix_str), suffix_str}),
                source};
        return {Result::just(IntegerConstant{value, suffix.value(), str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn floatingConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, floating_constant_re)) {
        auto str = std::string_view{source.begin() + match.position(), size_t(match.length())};
        auto value = std::string(source.begin() + match.position(), source.begin() + match.position(1));
        auto suffix_str = std::string_view{source.begin() + match.position(1), size_t(match.length(1))};
        auto suffix = core::types::floatingSuffixFromStr(std::string(suffix_str));
        if (not suffix.has_value())
            return {
                Result::error(
                    LexerError{std::format("invalid suffix \"{}\" on floating constant", suffix_str), suffix_str}),
                source};
        return {Result::just(FloatingConstant{value, suffix.value(), str}), source.substr(match.length())};
    }

    return {Result::nothing(), source};
}

LexerReturn characterConstant(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, character_constant_re)) {
        auto term_quote_pos = source.begin() + match.position() + match.length();
        if (term_quote_pos == source.end() or *term_quote_pos != '\'')
            return {
                Result::error(LexerError{
                    "missing terminating ' character",
                    std::string_view{source.begin() + match.position(), term_quote_pos}}),
                source};

        auto str = std::string_view{source.begin() + match.position(), term_quote_pos + 1};
        auto value = std::string(source.begin() + match.position(2), size_t(match.length(2)));
        auto prefix_str = std::string_view{source.begin() + match.position(), size_t(match.length(1))};
        auto prefix = core::types::encodingPrefixFromStr(std::string(prefix_str));
        if (not prefix.has_value())
            return {
                Result::error(LexerError{
                    std::format("invalid encoding prefix \"{}\" on character constant", prefix_str), prefix_str}),
                source};

        for (auto it = value.begin(); it != value.end(); ++it) {
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

        return {Result::just(CharacterConstant{value, prefix.value(), str}), source.substr(str.size())};
    }

    return {Result::nothing(), source};
}

LexerReturn stringLiteral(std::string_view source) {
    std::cmatch match;

    if (std::regex_search(source.begin(), source.end(), match, string_literal_re)) {
        auto term_quote_pos = source.begin() + match.position() + match.length();
        if (term_quote_pos == source.end() or *term_quote_pos != '"')
            return {
                Result::error(LexerError{
                    "missing terminating \" character",
                    std::string_view{source.begin() + match.position(), term_quote_pos}}),
                source};

        auto str = std::string_view{source.begin() + match.position(), term_quote_pos + 1};
        auto value = std::string(source.begin() + match.position(2), size_t(match.length(2)));
        auto prefix_str = std::string_view{source.begin() + match.position(), size_t(match.length(1))};
        auto prefix = core::types::encodingPrefixFromStr(std::string(prefix_str));
        if (not prefix.has_value())
            return {
                Result::error(LexerError{
                    std::format("invalid encoding prefix \"{}\" on character constant", prefix_str), prefix_str}),
                source};

        for (auto it = value.begin(); it != value.end(); ++it) {
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

        return {Result::just(StringLiteral{value, prefix.value(), {str}}), source.substr(str.size())};
    }

    return {Result::nothing(), source};
}

}  // namespace cless::fend::lexer::impl
