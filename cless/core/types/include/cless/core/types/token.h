#ifndef CLESS_CORE_TYPES_TOKEN_H
#define CLESS_CORE_TYPES_TOKEN_H

#include <iostream>
#include <string>
#include <variant>

namespace cless::core::types {

enum class TokenType {
    // Keywords
    Auto,
    Break,
    Bool,
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
    Extern,
    Float,
    For,
    Generic,
    Goto,
    If,
    Imaginary,
    Inline,
    Int,
    Long,
    Register,
    Restrict,
    Return,
    Short,
    Signed,
    Sizeof,
    Static,
    StaticAssert,
    Struct,
    Switch,
    Typedef,
    Union,
    Unsigned,
    Void,
    Volatile,
    While,

    // Punctuations
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

    Identifier,
    IntegerConstant,
    FloatingConstant,
    CharacterConstant,
    StringLiteral,
};

struct Token {
    TokenType type;
    std::string_view str;
};

std::string to_string(const Token& token);
std::ostream &operator<<(std::ostream &os, const Token& token);

}  // namespace cless::core::types

#endif
