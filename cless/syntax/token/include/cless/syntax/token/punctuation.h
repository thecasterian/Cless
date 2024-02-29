#ifndef CLESS_CORE_SYNTAX_PUNCTUATION_H
#define CLESS_CORE_SYNTAX_PUNCTUATION_H

#include <iostream>
#include <optional>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

enum class PunctuationType {
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
std::ostream &operator<<(std::ostream &os, PunctuationType type);
std::optional<PunctuationType> punctuationTypeFromStr(const std::string &str);

template <typename Derived>
struct Punctuation : public TokenBase {
    using TokenBase::TokenBase;
};

struct DoubleLessThanEqual : public Punctuation<DoubleLessThanEqual> {
    static constexpr PunctuationType type = PunctuationType::DoubleLessThanEqual;
    using Punctuation::Punctuation;
};

struct DoubleGreaterThanEqual : public Punctuation<DoubleGreaterThanEqual> {
    static constexpr PunctuationType type = PunctuationType::DoubleGreaterThanEqual;
    using Punctuation::Punctuation;
};

struct Ellipsis : public Punctuation<Ellipsis> {
    static constexpr PunctuationType type = PunctuationType::Ellipsis;
    using Punctuation::Punctuation;
};

struct Arrow : public Punctuation<Arrow> {
    static constexpr PunctuationType type = PunctuationType::Arrow;
    using Punctuation::Punctuation;
};

struct DoublePlus : public Punctuation<DoublePlus> {
    static constexpr PunctuationType type = PunctuationType::DoublePlus;
    using Punctuation::Punctuation;
};

struct DoubleMinus : public Punctuation<DoubleMinus> {
    static constexpr PunctuationType type = PunctuationType::DoubleMinus;
    using Punctuation::Punctuation;
};

struct DoubleLessThan : public Punctuation<DoubleLessThan> {
    static constexpr PunctuationType type = PunctuationType::DoubleLessThan;
    using Punctuation::Punctuation;
};

struct DoubleGreaterThan : public Punctuation<DoubleGreaterThan> {
    static constexpr PunctuationType type = PunctuationType::DoubleGreaterThan;
    using Punctuation::Punctuation;
};

struct LessThanEqual : public Punctuation<LessThanEqual> {
    static constexpr PunctuationType type = PunctuationType::LessThanEqual;
    using Punctuation::Punctuation;
};

struct GreaterThanEqual : public Punctuation<GreaterThanEqual> {
    static constexpr PunctuationType type = PunctuationType::GreaterThanEqual;
    using Punctuation::Punctuation;
};

struct DoubleEqual : public Punctuation<DoubleEqual> {
    static constexpr PunctuationType type = PunctuationType::DoubleEqual;
    using Punctuation::Punctuation;
};

struct ExclamationEqual : public Punctuation<ExclamationEqual> {
    static constexpr PunctuationType type = PunctuationType::ExclamationEqual;
    using Punctuation::Punctuation;
};

struct DoubleAmpersand : public Punctuation<DoubleAmpersand> {
    static constexpr PunctuationType type = PunctuationType::DoubleAmpersand;
    using Punctuation::Punctuation;
};

struct DoubleVerticalBar : public Punctuation<DoubleVerticalBar> {
    static constexpr PunctuationType type = PunctuationType::DoubleVerticalBar;
    using Punctuation::Punctuation;
};

struct AsteriskEqual : public Punctuation<AsteriskEqual> {
    static constexpr PunctuationType type = PunctuationType::AsteriskEqual;
    using Punctuation::Punctuation;
};

struct SlashEqual : public Punctuation<SlashEqual> {
    static constexpr PunctuationType type = PunctuationType::SlashEqual;
    using Punctuation::Punctuation;
};

struct PercentEqual : public Punctuation<PercentEqual> {
    static constexpr PunctuationType type = PunctuationType::PercentEqual;
    using Punctuation::Punctuation;
};

struct PlusEqual : public Punctuation<PlusEqual> {
    static constexpr PunctuationType type = PunctuationType::PlusEqual;
    using Punctuation::Punctuation;
};

struct MinusEqual : public Punctuation<MinusEqual> {
    static constexpr PunctuationType type = PunctuationType::MinusEqual;
    using Punctuation::Punctuation;
};

struct AmpersandEqual : public Punctuation<AmpersandEqual> {
    static constexpr PunctuationType type = PunctuationType::AmpersandEqual;
    using Punctuation::Punctuation;
};

struct CaretEqual : public Punctuation<CaretEqual> {
    static constexpr PunctuationType type = PunctuationType::CaretEqual;
    using Punctuation::Punctuation;
};

struct VerticalBarEqual : public Punctuation<VerticalBarEqual> {
    static constexpr PunctuationType type = PunctuationType::VerticalBarEqual;
    using Punctuation::Punctuation;
};

struct DoubleHash : public Punctuation<DoubleHash> {
    static constexpr PunctuationType type = PunctuationType::DoubleHash;
    using Punctuation::Punctuation;
};

struct OpenBracket : public Punctuation<OpenBracket> {
    static constexpr PunctuationType type = PunctuationType::OpenBracket;
    using Punctuation::Punctuation;
};

struct CloseBracket : public Punctuation<CloseBracket> {
    static constexpr PunctuationType type = PunctuationType::CloseBracket;
    using Punctuation::Punctuation;
};

struct OpenParenthesis : public Punctuation<OpenParenthesis> {
    static constexpr PunctuationType type = PunctuationType::OpenParenthesis;
    using Punctuation::Punctuation;
};

struct CloseParenthesis : public Punctuation<CloseParenthesis> {
    static constexpr PunctuationType type = PunctuationType::CloseParenthesis;
    using Punctuation::Punctuation;
};

struct OpenBrace : public Punctuation<OpenBrace> {
    static constexpr PunctuationType type = PunctuationType::OpenBrace;
    using Punctuation::Punctuation;
};

struct CloseBrace : public Punctuation<CloseBrace> {
    static constexpr PunctuationType type = PunctuationType::CloseBrace;
    using Punctuation::Punctuation;
};

struct Dot : public Punctuation<Dot> {
    static constexpr PunctuationType type = PunctuationType::Dot;
    using Punctuation::Punctuation;
};

struct Ampersand : public Punctuation<Ampersand> {
    static constexpr PunctuationType type = PunctuationType::Ampersand;
    using Punctuation::Punctuation;
};

struct Asterisk : public Punctuation<Asterisk> {
    static constexpr PunctuationType type = PunctuationType::Asterisk;
    using Punctuation::Punctuation;
};

struct Plus : public Punctuation<Plus> {
    static constexpr PunctuationType type = PunctuationType::Plus;
    using Punctuation::Punctuation;
};

struct Minus : public Punctuation<Minus> {
    static constexpr PunctuationType type = PunctuationType::Minus;
    using Punctuation::Punctuation;
};

struct Tilde : public Punctuation<Tilde> {
    static constexpr PunctuationType type = PunctuationType::Tilde;
    using Punctuation::Punctuation;
};

struct Exclamation : public Punctuation<Exclamation> {
    static constexpr PunctuationType type = PunctuationType::Exclamation;
    using Punctuation::Punctuation;
};

struct Slash : public Punctuation<Slash> {
    static constexpr PunctuationType type = PunctuationType::Slash;
    using Punctuation::Punctuation;
};

struct Percent : public Punctuation<Percent> {
    static constexpr PunctuationType type = PunctuationType::Percent;
    using Punctuation::Punctuation;
};

struct LessThan : public Punctuation<LessThan> {
    static constexpr PunctuationType type = PunctuationType::LessThan;
    using Punctuation::Punctuation;
};

struct GreaterThan : public Punctuation<GreaterThan> {
    static constexpr PunctuationType type = PunctuationType::GreaterThan;
    using Punctuation::Punctuation;
};

struct Caret : public Punctuation<Caret> {
    static constexpr PunctuationType type = PunctuationType::Caret;
    using Punctuation::Punctuation;
};

struct VerticalBar : public Punctuation<VerticalBar> {
    static constexpr PunctuationType type = PunctuationType::VerticalBar;
    using Punctuation::Punctuation;
};

struct Question : public Punctuation<Question> {
    static constexpr PunctuationType type = PunctuationType::Question;
    using Punctuation::Punctuation;
};

struct Colon : public Punctuation<Colon> {
    static constexpr PunctuationType type = PunctuationType::Colon;
    using Punctuation::Punctuation;
};

struct Semicolon : public Punctuation<Semicolon> {
    static constexpr PunctuationType type = PunctuationType::Semicolon;
    using Punctuation::Punctuation;
};

struct Equal : public Punctuation<Equal> {
    static constexpr PunctuationType type = PunctuationType::Equal;
    using Punctuation::Punctuation;
};

struct Comma : public Punctuation<Comma> {
    static constexpr PunctuationType type = PunctuationType::Comma;
    using Punctuation::Punctuation;
};

struct Hash : public Punctuation<Hash> {
    static constexpr PunctuationType type = PunctuationType::Hash;
    using Punctuation::Punctuation;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Punctuation<T> &) {
    return os << "Punctuation " << T::type, os;
}

}  // namespace cless::syntax::token

#endif
