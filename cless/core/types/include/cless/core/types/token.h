#ifndef CLESS_CORE_TYPES_TOKEN_H
#define CLESS_CORE_TYPES_TOKEN_H

#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace cless::core::types {

enum class KeywordType {
    Alignas,
    Alignof,
    Auto,
    Bool,
    Break,
    Case,
    Char,
    Complex,
    Const,
    Continue,
    Default,
    Do,
    Double,
    Else,
    Enum,
    False,
    Float,
    For,
    Generic,
    If,
    Imaginary,
    Inline,
    Int,
    Long,
    NullPtr,
    Restrict,
    Return,
    Short,
    Signed,
    Sizeof,
    Static,
    StaticAssert,
    Struct,
    Switch,
    True,
    Typedef,
    Typeof,
    Union,
    Unsigned,
    Void,
    Volatile,
    While,
};

struct Keyword {
    KeywordType type;
    std::string_view source;
};

enum class PunctuationType {
    OpenBracket,
    CloseBracket,
    OpenParenthesis,
    CloseParenthesis,
    OpenBrace,
    CloseBrace,
    Dot,
    Arrow,
    DoublePlus,
    DoubleMinus,
    Ampersand,
    Asterisk,
    Plus,
    Minus,
    Tilde,
    Exclamation,
    Slash,
    Percent,
    DoubleLessThan,
    DoubleGreaterThan,
    LessThan,
    GreaterThan,
    LessThanOrEqualTo,
    GreaterThanOrEqualTo,
    DoubleEqual,
    ExclamationEqual,
    Caret,
    VerticalBar,
    DoubleAmpersand,
    DoubleVerticalBar,
    Question,
    Colon,
    Semicolon,
    Ellipsis,
    Equal,
    AsteriskEqual,
    SlashEqual,
    PercentEqual,
    PlusEqual,
    MinusEqual,
    DoubleLessThanEqual,
    DoubleGreaterThanEqual,
    AmpersandEqual,
    CaretEqual,
    VerticalBarEqual,
    Comma,
};

struct Punctuation {
    PunctuationType type;
    std::string_view source;
};

struct Identifier {
    std::string name;
    std::string_view source;
};

enum class IntegerSuffix {
    None,
    Unsigned,
    Long,
    UnsignedLong,
    LongLong,
    UnsignedLongLong,
};

std::string toString(IntegerSuffix integer_suffix);
std::optional<IntegerSuffix> integerSuffixFromStr(const std::string& str);

struct IntegerConstant {
    std::string value;
    IntegerSuffix suffix;
    std::string_view source;
};

enum class FloatingSuffix {
    None,
    Float,
    LongDouble,
};

struct FloatingConstant {
    std::string value;
    FloatingSuffix suffix;
    std::string_view source;
};

std::string toString(FloatingSuffix floating_suffix);
std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string& str);

enum class EncodingPrefix {
    None,
    UTF8,
    WChar,
    Char16,
    Char32,
};

std::string toString(EncodingPrefix encoding_prefix);
std::optional<EncodingPrefix> encodingPrefixFromStr(const std::string& str);

struct CharacterConstant {
    std::string value;
    EncodingPrefix prefix;
    std::string_view source;
};

struct StringLiteral {
    std::string value;
    EncodingPrefix prefix;
    std::vector<std::string_view> sources;
};

struct Token : public std::variant<
                   Keyword,
                   Punctuation,
                   Identifier,
                   IntegerConstant,
                   FloatingConstant,
                   CharacterConstant,
                   StringLiteral> {
    using variant::variant;

    bool isKeyword() const;
    bool isKeyword(KeywordType type) const;
    bool isPunctuation() const;
    bool isPunctuation(PunctuationType type) const;
    bool isIdentifier() const;
    bool isIntegerConstant() const;
    bool isFloatingConstant() const;
    bool isCharacterConstant() const;
    bool isStringLiteral() const;

    const char* sourceBegin() const;
    const char* sourceEnd() const;
};

std::string toString(const Token& token);
std::ostream& operator<<(std::ostream& os, const Token& token);

}  // namespace cless::core::types

#endif
