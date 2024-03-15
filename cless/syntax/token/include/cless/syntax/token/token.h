#ifndef CLESS_CORE_SYNTAX_TOKEN_H
#define CLESS_CORE_SYNTAX_TOKEN_H

#include <variant>

#include "cless/syntax/token/constant.h"
#include "cless/syntax/token/header_name.h"
#include "cless/syntax/token/identifier.h"
#include "cless/syntax/token/keyword.h"
#include "cless/syntax/token/punctuation.h"
#include "cless/syntax/token/string_literal.h"

namespace cless::syntax::token {

struct Token : public std::variant<
                   // keywords
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
                   // punctuations
                   DoubleLessThanEqual,
                   DoubleGreaterThanEqual,
                   Ellipsis,
                   Arrow,
                   DoublePlus,
                   DoubleMinus,
                   DoubleLessThan,
                   DoubleGreaterThan,
                   LessThanEqual,
                   GreaterThanEqual,
                   DoubleEqual,
                   ExclamationEqual,
                   DoubleAmpersand,
                   DoubleVerticalBar,
                   AsteriskEqual,
                   SlashEqual,
                   PercentEqual,
                   PlusEqual,
                   MinusEqual,
                   AmpersandEqual,
                   CaretEqual,
                   VerticalBarEqual,
                   DoubleHash,
                   OpenBracket,
                   CloseBracket,
                   OpenParenthesis,
                   CloseParenthesis,
                   OpenBrace,
                   CloseBrace,
                   Dot,
                   Ampersand,
                   Asterisk,
                   Plus,
                   Minus,
                   Tilde,
                   Exclamation,
                   Slash,
                   Percent,
                   LessThan,
                   GreaterThan,
                   Caret,
                   VerticalBar,
                   Question,
                   Colon,
                   Semicolon,
                   Equal,
                   Comma,
                   Hash,
                   // identifier
                   Identifier,
                   // constants
                   IntegerConstant,
                   FloatingConstant,
                   CharacterConstant,
                   // string literal
                   StringLiteral> {
    using variant::variant;
};

std::ostream &operator<<(std::ostream &os, const Token &token);

struct PreprocessingToken : public std::variant<
                                // header name
                                HeaderName,
                                // punctuations
                                DoubleLessThanEqual,
                                DoubleGreaterThanEqual,
                                Ellipsis,
                                Arrow,
                                DoublePlus,
                                DoubleMinus,
                                DoubleLessThan,
                                DoubleGreaterThan,
                                LessThanEqual,
                                GreaterThanEqual,
                                DoubleEqual,
                                ExclamationEqual,
                                DoubleAmpersand,
                                DoubleVerticalBar,
                                AsteriskEqual,
                                SlashEqual,
                                PercentEqual,
                                PlusEqual,
                                MinusEqual,
                                AmpersandEqual,
                                CaretEqual,
                                VerticalBarEqual,
                                DoubleHash,
                                OpenBracket,
                                CloseBracket,
                                OpenParenthesis,
                                CloseParenthesis,
                                OpenBrace,
                                CloseBrace,
                                Dot,
                                Ampersand,
                                Asterisk,
                                Plus,
                                Minus,
                                Tilde,
                                Exclamation,
                                Slash,
                                Percent,
                                LessThan,
                                GreaterThan,
                                Caret,
                                VerticalBar,
                                Question,
                                Colon,
                                Semicolon,
                                Equal,
                                Comma,
                                Hash,
                                // identifier
                                Identifier,
                                // constants
                                IntegerConstant,
                                FloatingConstant,
                                CharacterConstant,
                                // string literal
                                StringLiteral> {
    using variant::variant;
};

std::ostream &operator<<(std::ostream &os, const PreprocessingToken &pp_token);
Token toToken(const PreprocessingToken &pp_token);

}  // namespace cless::syntax::token

#endif
