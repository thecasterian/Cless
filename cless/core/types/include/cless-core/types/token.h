#ifndef CLESS_CORE_TYPES_TOKEN_H
#define CLESS_CORE_TYPES_TOKEN_H

#include <iostream>
#include <string>
#include <variant>

namespace cless::core::types {

namespace token {

namespace keyword {

struct Auto {};
struct Break {};
struct Bool {};
struct Case {};
struct Char {};
struct Complex {};
struct Const {};
struct Continue {};
struct Default {};
struct Do {};
struct Double {};
struct Else {};
struct Enum {};
struct Extern {};
struct Float {};
struct For {};
struct Generic {};
struct Goto {};
struct If {};
struct Imaginary {};
struct Inline {};
struct Int {};
struct Long {};
struct Register {};
struct Restrict {};
struct Return {};
struct Short {};
struct Signed {};
struct Sizeof {};
struct Static {};
struct StaticAssert {};
struct Struct {};
struct Switch {};
struct Typedef {};
struct Union {};
struct Unsigned {};
struct Void {};
struct Volatile {};
struct While {};

}  // namespace keyword

namespace punct {

struct OpenBracket {};
struct CloseBracket {};
struct OpenParen {};
struct CloseParen {};
struct OpenBrace {};
struct CloseBrace {};
struct Dot {};
struct Arrow {};
struct DoublePlus {};
struct DoubleMinus {};
struct Ampersand {};
struct Asterisk {};
struct Plus {};
struct Minus {};
struct Tilde {};
struct Exclamation {};
struct Slash {};
struct Percent {};
struct DoubleLessThan {};
struct DoubleGreaterThan {};
struct LessThan {};
struct GreaterThan {};
struct LessThanOrEqualTo {};
struct GreaterThanOrEqualTo {};
struct DoubleEqual {};
struct ExclamationEqual {};
struct Caret {};
struct VerticalBar {};
struct DoubleAmpersand {};
struct DoubleVerticalBar {};
struct Question {};
struct Colon {};
struct Semicolon {};
struct Ellipsis {};
struct Equal {};
struct AsteriskEqual {};
struct SlashEqual {};
struct PercentEqual {};
struct PlusEqual {};
struct MinusEqual {};
struct DoubleLessThanEqual {};
struct DoubleGreaterThanEqual {};
struct AmpersandEqual {};
struct CaretEqual {};
struct VerticalBarEqual {};
struct Comma {};

}  // namespace punct

struct Identifier {
    std::string name;
};

struct IntegerConstant {
    std::string value;
};

struct FloatingConstant {
    std::string value;
};

struct CharacterConstant {
    std::string value;
};

struct StringLiteral {
    std::string value;
};

}  // namespace token

using Token = std::variant<
    token::keyword::Auto,
    token::keyword::Break,
    token::keyword::Bool,
    token::keyword::Case,
    token::keyword::Char,
    token::keyword::Complex,
    token::keyword::Const,
    token::keyword::Continue,
    token::keyword::Default,
    token::keyword::Do,
    token::keyword::Double,
    token::keyword::Else,
    token::keyword::Enum,
    token::keyword::Extern,
    token::keyword::Float,
    token::keyword::For,
    token::keyword::Generic,
    token::keyword::Goto,
    token::keyword::If,
    token::keyword::Imaginary,
    token::keyword::Inline,
    token::keyword::Int,
    token::keyword::Long,
    token::keyword::Register,
    token::keyword::Restrict,
    token::keyword::Return,
    token::keyword::Short,
    token::keyword::Signed,
    token::keyword::Sizeof,
    token::keyword::Static,
    token::keyword::StaticAssert,
    token::keyword::Struct,
    token::keyword::Switch,
    token::keyword::Typedef,
    token::keyword::Union,
    token::keyword::Unsigned,
    token::keyword::Void,
    token::keyword::Volatile,
    token::keyword::While,
    token::punct::OpenBracket,
    token::punct::CloseBracket,
    token::punct::OpenParen,
    token::punct::CloseParen,
    token::punct::OpenBrace,
    token::punct::CloseBrace,
    token::punct::Dot,
    token::punct::Arrow,
    token::punct::DoublePlus,
    token::punct::DoubleMinus,
    token::punct::Ampersand,
    token::punct::Asterisk,
    token::punct::Plus,
    token::punct::Minus,
    token::punct::Tilde,
    token::punct::Exclamation,
    token::punct::Slash,
    token::punct::Percent,
    token::punct::DoubleLessThan,
    token::punct::DoubleGreaterThan,
    token::punct::LessThan,
    token::punct::GreaterThan,
    token::punct::LessThanOrEqualTo,
    token::punct::GreaterThanOrEqualTo,
    token::punct::DoubleEqual,
    token::punct::ExclamationEqual,
    token::punct::Caret,
    token::punct::VerticalBar,
    token::punct::DoubleAmpersand,
    token::punct::DoubleVerticalBar,
    token::punct::Question,
    token::punct::Colon,
    token::punct::Semicolon,
    token::punct::Ellipsis,
    token::punct::Equal,
    token::punct::AsteriskEqual,
    token::punct::SlashEqual,
    token::punct::PercentEqual,
    token::punct::PlusEqual,
    token::punct::MinusEqual,
    token::punct::DoubleLessThanEqual,
    token::punct::DoubleGreaterThanEqual,
    token::punct::AmpersandEqual,
    token::punct::CaretEqual,
    token::punct::VerticalBarEqual,
    token::punct::Comma,
    token::Identifier,
    token::IntegerConstant,
    token::FloatingConstant,
    token::CharacterConstant,
    token::StringLiteral>;
std::string to_string(const Token& token);
std::ostream& operator<<(std::ostream& os, const Token& token);

struct TokenInfo {
    size_t line_no;
    size_t start;
    size_t end;
};

}  // namespace cless::core::types

#endif
