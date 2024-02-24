#ifndef CLESS_CORE_TYPES_TOKEN_H
#define CLESS_CORE_TYPES_TOKEN_H

#include <iostream>
#include <optional>
#include <string>
#include <variant>

namespace cless::core::types {

// C89 keywords
enum class Keyword {
    Continue,
    Register,
    Unsigned,
    Volatile,
    Default,
    Typedef,
    Double,
    Extern,
    Return,
    Signed,
    Sizeof,
    Static,
    Struct,
    Switch,
    Break,
    Const,
    Float,
    Short,
    While,
    Union,
    Auto,
    Case,
    Char,
    Else,
    Enum,
    Goto,
    Long,
    Void,
    For,
    Int,
    Do,
    If,
};

std::string toString(Keyword keyword);
std::optional<Keyword> keywordFromStr(const std::string& str);

enum class Punctuation {
    DoubleLessThanEqual,     // <<=
    DoubleGreaterThanEqual,  // >>=
    Ellipsis,                // ...
    Arrow,                   // ->
    DoublePlus,              // ++
    DoubleMinus,             // --
    DoubleLessThan,          // <<
    DoubleGreaterThan,       // >>
    LessThanEqual,           // <=
    GreaterThanEqual,        // >=
    DoubleEqual,             // ==
    ExclamationEqual,        // !=
    DoubleAmpersand,         // &&
    DoubleVerticalBar,       // ||
    AsteriskEqual,           // *=
    SlashEqual,              // /=
    PercentEqual,            // %=
    PlusEqual,               // +=
    MinusEqual,              // -=
    AmpersandEqual,          // &=
    CaretEqual,              // ^=
    VerticalBarEqual,        // |=
    DoubleHash,              // ##
    OpenBracket,             // [
    CloseBracket,            // ]
    OpenParenthesis,         // (
    CloseParenthesis,        // )
    OpenBrace,               // {
    CloseBrace,              // }
    Dot,                     // .
    Ampersand,               // &
    Asterisk,                // *
    Plus,                    // +
    Minus,                   // -
    Tilde,                   // ~
    Exclamation,             // !
    Slash,                   // /
    Percent,                 // %
    LessThan,                // <
    GreaterThan,             // >
    Caret,                   // ^
    VerticalBar,             // |
    Question,                // ?
    Colon,                   // :
    Semicolon,               // ;
    Equal,                   // =
    Comma,                   // ,
    Hash,                    // #
};

std::string toString(Punctuation punct);
std::optional<Punctuation> punctuationFromStr(const std::string& str);

struct Identifier {
    std::string name;
};

enum class IntegerSuffix {
    None,
    Unsigned,
    Long,
    UnsignedLong,
    LongLong,
    UnsignedLongLong,
};

std::string toString(IntegerSuffix int_suffix);
std::optional<IntegerSuffix> integerSuffixFromStr(const std::string& str);

enum class IntegerBase {
    Decimal,
    Octal,
    Hexadecimal,
};

std::string toString(IntegerBase int_base);
std::optional<IntegerBase> integerBaseFromStr(const std::string& str);

struct IntegerConstant {
    IntegerBase base;
    std::string value;
    IntegerSuffix suffix;
};

enum class FloatingSuffix {
    None,
    Float,
    LongDouble,
};

std::string toString(FloatingSuffix float_suffix);
std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string& str);

struct FloatingConstant {
    std::string value;
    FloatingSuffix suffix;
};

struct CharacterConstant {
    std::string value;
};

struct StringLiteral {
    std::string value;
};

struct Token : public std::variant<
                   Keyword,
                   Punctuation,
                   Identifier,
                   IntegerConstant,
                   FloatingConstant,
                   CharacterConstant,
                   StringLiteral> {
    std::string file;
    std::size_t line_start, line_end;
    std::size_t col_start, col_end;

    template <typename T>
    Token(
        T&& value,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end)
        : variant(std::forward<T>(value)),
          file(std::move(file)),
          line_start(line_start),
          line_end(line_end),
          col_start(col_start),
          col_end(col_end) {}

    bool isKeyword() const;
    bool isKeyword(Keyword keyword) const;
    bool isPunctuation() const;
    bool isPunctuation(Punctuation punct) const;
    bool isIdentifier() const;
    bool isIntegerConstant() const;
    bool isFloatingConstant() const;
    bool isCharacterConstant() const;
    bool isStringLiteral() const;
};

std::string toString(const Token& token);
std::ostream& operator<<(std::ostream& os, const Token& token);

struct HeaderName {
    std::string name;
    bool is_system;  // <...> vs "..."
};

struct PreprocessingToken : public std::variant<
                                HeaderName,
                                Identifier,
                                Punctuation,
                                IntegerConstant,
                                FloatingConstant,
                                CharacterConstant,
                                StringLiteral> {
    std::string file;
    std::size_t line_start, line_end;
    std::size_t col_start, col_end;

    template <typename T>
    PreprocessingToken(
        T&& value,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end)
        : variant(std::forward<T>(value)),
          file(std::move(file)),
          line_start(line_start),
          line_end(line_end),
          col_start(col_start),
          col_end(col_end) {}

    bool isHeaderName() const;
    bool isIdentifier() const;
    bool isPunctuation() const;
    bool isPunctuation(Punctuation type) const;
    bool isIntegerConstant() const;
    bool isFloatingConstant() const;
    bool isCharacterConstant() const;
    bool isStringLiteral() const;
};

Token toToken(const PreprocessingToken& pp_token);

std::string toString(const PreprocessingToken& pp_token);
std::ostream& operator<<(std::ostream& os, const PreprocessingToken& pp_token);

}  // namespace cless::core::types

#endif
