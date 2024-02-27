#include "cless/core/types/token.h"

#include <array>
#include <format>

#include "cless/core/types/exception.h"

namespace cless::core::types {
using types::Exception;

struct KeywordString {
    Keyword keyword;
    const char *str;
};

struct PunctuationString {
    Punctuation punct;
    const char *str;
};

constexpr std::array<KeywordString, 32> keyword_table{
    KeywordString{Keyword::Continue, "continue"},
    KeywordString{Keyword::Register, "register"},
    KeywordString{Keyword::Unsigned, "unsigned"},
    KeywordString{Keyword::Volatile, "volatile"},
    KeywordString{Keyword::Default, "default"},
    KeywordString{Keyword::Typedef, "typedef"},
    KeywordString{Keyword::Double, "double"},
    KeywordString{Keyword::Extern, "extern"},
    KeywordString{Keyword::Return, "return"},
    KeywordString{Keyword::Signed, "signed"},
    KeywordString{Keyword::Sizeof, "sizeof"},
    KeywordString{Keyword::Static, "static"},
    KeywordString{Keyword::Struct, "struct"},
    KeywordString{Keyword::Switch, "switch"},
    KeywordString{Keyword::Break, "break"},
    KeywordString{Keyword::Const, "const"},
    KeywordString{Keyword::Float, "float"},
    KeywordString{Keyword::Short, "short"},
    KeywordString{Keyword::While, "while"},
    KeywordString{Keyword::Union, "union"},
    KeywordString{Keyword::Auto, "auto"},
    KeywordString{Keyword::Case, "case"},
    KeywordString{Keyword::Char, "char"},
    KeywordString{Keyword::Else, "else"},
    KeywordString{Keyword::Enum, "enum"},
    KeywordString{Keyword::Goto, "goto"},
    KeywordString{Keyword::Long, "long"},
    KeywordString{Keyword::Void, "void"},
    KeywordString{Keyword::For, "for"},
    KeywordString{Keyword::Int, "int"},
    KeywordString{Keyword::Do, "do"},
    KeywordString{Keyword::If, "if"},
};

constexpr std::array<PunctuationString, 48> punctuation_table{
    PunctuationString{Punctuation::DoubleLessThanEqual, "<<="},
    PunctuationString{Punctuation::DoubleGreaterThanEqual, ">>="},
    PunctuationString{Punctuation::Ellipsis, "..."},
    PunctuationString{Punctuation::Arrow, "->"},
    PunctuationString{Punctuation::DoublePlus, "++"},
    PunctuationString{Punctuation::DoubleMinus, "--"},
    PunctuationString{Punctuation::DoubleLessThan, "<<"},
    PunctuationString{Punctuation::DoubleGreaterThan, ">>"},
    PunctuationString{Punctuation::LessThanEqual, "<="},
    PunctuationString{Punctuation::GreaterThanEqual, ">="},
    PunctuationString{Punctuation::DoubleEqual, "=="},
    PunctuationString{Punctuation::ExclamationEqual, "!="},
    PunctuationString{Punctuation::DoubleAmpersand, "&&"},
    PunctuationString{Punctuation::DoubleVerticalBar, "||"},
    PunctuationString{Punctuation::AsteriskEqual, "*="},
    PunctuationString{Punctuation::SlashEqual, "/="},
    PunctuationString{Punctuation::PercentEqual, "%="},
    PunctuationString{Punctuation::PlusEqual, "+="},
    PunctuationString{Punctuation::MinusEqual, "-="},
    PunctuationString{Punctuation::AmpersandEqual, "&="},
    PunctuationString{Punctuation::CaretEqual, "^="},
    PunctuationString{Punctuation::VerticalBarEqual, "|="},
    PunctuationString{Punctuation::DoubleHash, "##"},
    PunctuationString{Punctuation::OpenBracket, "["},
    PunctuationString{Punctuation::CloseBracket, "]"},
    PunctuationString{Punctuation::OpenParenthesis, "("},
    PunctuationString{Punctuation::CloseParenthesis, ")"},
    PunctuationString{Punctuation::OpenBrace, "{"},
    PunctuationString{Punctuation::CloseBrace, "}"},
    PunctuationString{Punctuation::Dot, "."},
    PunctuationString{Punctuation::Ampersand, "&"},
    PunctuationString{Punctuation::Asterisk, "*"},
    PunctuationString{Punctuation::Plus, "+"},
    PunctuationString{Punctuation::Minus, "-"},
    PunctuationString{Punctuation::Tilde, "~"},
    PunctuationString{Punctuation::Exclamation, "!"},
    PunctuationString{Punctuation::Slash, "/"},
    PunctuationString{Punctuation::Percent, "%"},
    PunctuationString{Punctuation::LessThan, "<"},
    PunctuationString{Punctuation::GreaterThan, ">"},
    PunctuationString{Punctuation::Caret, "^"},
    PunctuationString{Punctuation::VerticalBar, "|"},
    PunctuationString{Punctuation::Question, "?"},
    PunctuationString{Punctuation::Colon, ":"},
    PunctuationString{Punctuation::Semicolon, ";"},
    PunctuationString{Punctuation::Equal, "="},
    PunctuationString{Punctuation::Comma, ","},
    PunctuationString{Punctuation::Hash, "#"},
};

std::string toString(Keyword keyword) {
    for (const auto &entry : keyword_table)
        if (entry.keyword == keyword)
            return entry.str;
    throw Exception("Unknown keyword");
}

std::optional<Keyword> keywordFromStr(const std::string &str) {
    for (const auto &entry : keyword_table)
        if (entry.str == str)
            return entry.keyword;
    return std::nullopt;
}

std::string toString(Punctuation punct) {
    for (const auto &entry : punctuation_table)
        if (entry.punct == punct)
            return entry.str;
    throw Exception("Unknown punctuation");
}

std::optional<Punctuation> punctuationFromStr(const std::string &str) {
    for (const auto &entry : punctuation_table)
        if (entry.str == str)
            return entry.punct;
    return std::nullopt;
}

std::string toString(IntegerSuffix int_suffix) {
    switch (int_suffix) {
        case IntegerSuffix::None:
            return "";
        case IntegerSuffix::Unsigned:
            return "u";
        case IntegerSuffix::Long:
            return "l";
        case IntegerSuffix::UnsignedLong:
            return "ul";
        case IntegerSuffix::LongLong:
            return "ll";
        case IntegerSuffix::UnsignedLongLong:
            return "ull";
    }

    throw Exception("Unknown integer suffix");
}

std::optional<IntegerSuffix> integerSuffixFromStr(const std::string &str) {
    if (str == "")
        return IntegerSuffix::None;
    else if (str == "u" or str == "U")
        return IntegerSuffix::Unsigned;
    else if (str == "l" or str == "L")
        return IntegerSuffix::Long;
    else if (str == "ul" or str == "lu" or str == "UL" or str == "LU")
        return IntegerSuffix::UnsignedLong;
    else if (str == "ll" or str == "LL")
        return IntegerSuffix::LongLong;
    else if (
        str == "ull" or str == "llu" or str == "uLL" or str == "LLu" or str == "Ull" or str == "llU" or str == "ULL" or
        str == "LLU")
        return IntegerSuffix::UnsignedLongLong;
    else
        return std::nullopt;
}

std::string toString(FloatingSuffix float_suffix) {
    switch (float_suffix) {
        case FloatingSuffix::None:
            return "";
        case FloatingSuffix::Float:
            return "f";
        case FloatingSuffix::LongDouble:
            return "l";
    }

    throw Exception("Unknown floating suffix");
}

std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string &str) {
    if (str == "")
        return FloatingSuffix::None;
    else if (str == "f" or str == "F")
        return FloatingSuffix::Float;
    else if (str == "l" or str == "L")
        return FloatingSuffix::LongDouble;
    else
        return std::nullopt;
}

struct TokenToStringVisitor {
    std::string operator()(Keyword keyword) const { return std::format("Keyword({})", toString(keyword)); }

    std::string operator()(Punctuation punct) const { return toString(punct); }

    std::string operator()(const Identifier &identifier) const {
        return std::format("Identifier({})", identifier.name);
    }

    std::string operator()(const IntegerConstant &int_constant) const {
        return std::format("Integer({}{})", int_constant.value, toString(int_constant.suffix));
    }

    std::string operator()(const FloatingConstant &float_const) const {
        return std::format("Floating({}{})", float_const.value, toString(float_const.suffix));
    }

    std::string operator()(const CharacterConstant &char_const) const {
        return std::format("Character({})", char_const.value);
    }

    std::string operator()(const StringLiteral &string_literal) const {
        return std::format("String(\"{}\")", string_literal.value);
    }
};

bool Token::isKeyword() const {
    return std::holds_alternative<Keyword>(*this);
}

bool Token::isKeyword(Keyword keyword) const {
    return std::holds_alternative<Keyword>(*this) and std::get<Keyword>(*this) == keyword;
}

bool Token::isPunctuation() const {
    return std::holds_alternative<Punctuation>(*this);
}

bool Token::isPunctuation(Punctuation punct) const {
    return std::holds_alternative<Punctuation>(*this) and std::get<Punctuation>(*this) == punct;
}

bool Token::isIdentifier() const {
    return std::holds_alternative<Identifier>(*this);
}

bool Token::isIntegerConstant() const {
    return std::holds_alternative<IntegerConstant>(*this);
}

bool Token::isFloatingConstant() const {
    return std::holds_alternative<FloatingConstant>(*this);
}

bool Token::isCharacterConstant() const {
    return std::holds_alternative<CharacterConstant>(*this);
}

bool Token::isStringLiteral() const {
    return std::holds_alternative<StringLiteral>(*this);
}

std::string toString(const Token &token) {
    return std::visit(TokenToStringVisitor{}, token);
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << toString(token) << " at " << token.file << ":" << token.line_start << ":" << token.col_start;
    return os;
}

struct PreprocessingTokenToStringVisitor {
    std::string operator()(const HeaderName &header_name) const {
        return std::format(
            "{}{}{}", header_name.is_system ? "<" : "\"", header_name.name, header_name.is_system ? ">" : "\"");
    }

    std::string operator()(Punctuation punct) const { return toString(punct); }

    std::string operator()(const Identifier &identifier) const { return identifier.name; }

    std::string operator()(const IntegerConstant &int_constant) const {
        return std::format("{}{}", int_constant.value, toString(int_constant.suffix));
    }

    std::string operator()(const FloatingConstant &float_const) const {
        return std::format("{}{}", float_const.value, toString(float_const.suffix));
    }

    std::string operator()(const CharacterConstant &char_const) const { return std::format("'{}'", char_const.value); }

    std::string operator()(const StringLiteral &string_literal) const {
        return std::format("\"{}\"", string_literal.value);
    }
};

bool PreprocessingToken::isHeaderName() const {
    return std::holds_alternative<HeaderName>(*this);
}

bool PreprocessingToken::isIdentifier() const {
    return std::holds_alternative<Identifier>(*this);
}

bool PreprocessingToken::isPunctuation() const {
    return std::holds_alternative<Punctuation>(*this);
}

bool PreprocessingToken::isPunctuation(Punctuation punct) const {
    return std::holds_alternative<Punctuation>(*this) and std::get<Punctuation>(*this) == punct;
}

bool PreprocessingToken::isIntegerConstant() const {
    return std::holds_alternative<IntegerConstant>(*this);
}

bool PreprocessingToken::isFloatingConstant() const {
    return std::holds_alternative<FloatingConstant>(*this);
}

bool PreprocessingToken::isCharacterConstant() const {
    return std::holds_alternative<CharacterConstant>(*this);
}

bool PreprocessingToken::isStringLiteral() const {
    return std::holds_alternative<StringLiteral>(*this);
}

Token toToken(const PreprocessingToken &pp_token) {
    if (pp_token.isIdentifier()) {
        auto ident = std::get<Identifier>(pp_token);
        if (auto keyword = keywordFromStr(ident.name); keyword.has_value())
            return Token(
                keyword.value(),
                pp_token.file,
                pp_token.line_start,
                pp_token.col_start,
                pp_token.line_end,
                pp_token.col_end);
        return Token(
            ident, pp_token.file, pp_token.line_start, pp_token.col_start, pp_token.line_end, pp_token.col_end);
    } else if (pp_token.isPunctuation()) {
        return Token(
            std::get<Punctuation>(pp_token),
            pp_token.file,
            pp_token.line_start,
            pp_token.col_start,
            pp_token.line_end,
            pp_token.col_end);
    } else if (pp_token.isIntegerConstant()) {
        return Token(
            std::get<IntegerConstant>(pp_token),
            pp_token.file,
            pp_token.line_start,
            pp_token.col_start,
            pp_token.line_end,
            pp_token.col_end);
    } else if (pp_token.isFloatingConstant()) {
        return Token(
            std::get<FloatingConstant>(pp_token),
            pp_token.file,
            pp_token.line_start,
            pp_token.col_start,
            pp_token.line_end,
            pp_token.col_end);
    } else if (pp_token.isCharacterConstant()) {
        return Token(
            std::get<CharacterConstant>(pp_token),
            pp_token.file,
            pp_token.line_start,
            pp_token.col_start,
            pp_token.line_end,
            pp_token.col_end);
    } else if (pp_token.isStringLiteral()) {
        return Token(
            std::get<StringLiteral>(pp_token),
            pp_token.file,
            pp_token.line_start,
            pp_token.col_start,
            pp_token.line_end,
            pp_token.col_end);
    }
    throw Exception("Cannot convert PreprocessingToken to Token");
}

std::string toString(const PreprocessingToken &pp_token) {
    return std::visit(PreprocessingTokenToStringVisitor{}, pp_token);
}

std::ostream &operator<<(std::ostream &os, const PreprocessingToken &pp_token) {
    os << toString(pp_token);
    return os;
}

}  // namespace cless::core::types
