#ifndef CLESS_CORE_SYNTAX_KEYWORD_H
#define CLESS_CORE_SYNTAX_KEYWORD_H

#include <iostream>
#include <optional>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

enum class KeywordType {
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
std::ostream &operator<<(std::ostream &os, KeywordType type);
std::optional<KeywordType> keywordTypeFromStr(const std::string &str);

template <typename Derived>
struct Keyword : public TokenBase {
    using TokenBase::TokenBase;
};

struct Continue : public Keyword<Continue> {
    static constexpr KeywordType type = KeywordType::Continue;
    using Keyword::Keyword;
};

struct Register : public Keyword<Register> {
    static constexpr KeywordType type = KeywordType::Register;
    using Keyword::Keyword;
};

struct Unsigned : public Keyword<Unsigned> {
    static constexpr KeywordType type = KeywordType::Unsigned;
    using Keyword::Keyword;
};

struct Volatile : public Keyword<Volatile> {
    static constexpr KeywordType type = KeywordType::Volatile;
    using Keyword::Keyword;
};

struct Default : public Keyword<Default> {
    static constexpr KeywordType type = KeywordType::Default;
    using Keyword::Keyword;
};

struct Typedef : public Keyword<Typedef> {
    static constexpr KeywordType type = KeywordType::Typedef;
    using Keyword::Keyword;
};

struct Double : public Keyword<Double> {
    static constexpr KeywordType type = KeywordType::Double;
    using Keyword::Keyword;
};

struct Extern : public Keyword<Extern> {
    static constexpr KeywordType type = KeywordType::Extern;
    using Keyword::Keyword;
};

struct Return : public Keyword<Return> {
    static constexpr KeywordType type = KeywordType::Return;
    using Keyword::Keyword;
};

struct Signed : public Keyword<Signed> {
    static constexpr KeywordType type = KeywordType::Signed;
    using Keyword::Keyword;
};

struct Sizeof : public Keyword<Sizeof> {
    static constexpr KeywordType type = KeywordType::Sizeof;
    using Keyword::Keyword;
};

struct Static : public Keyword<Static> {
    static constexpr KeywordType type = KeywordType::Static;
    using Keyword::Keyword;
};

struct Struct : public Keyword<Struct> {
    static constexpr KeywordType type = KeywordType::Struct;
    using Keyword::Keyword;
};

struct Switch : public Keyword<Switch> {
    static constexpr KeywordType type = KeywordType::Switch;
    using Keyword::Keyword;
};

struct Break : public Keyword<Break> {
    static constexpr KeywordType type = KeywordType::Break;
    using Keyword::Keyword;
};

struct Const : public Keyword<Const> {
    static constexpr KeywordType type = KeywordType::Const;
    using Keyword::Keyword;
};

struct Float : public Keyword<Float> {
    static constexpr KeywordType type = KeywordType::Float;
    using Keyword::Keyword;
};

struct Short : public Keyword<Short> {
    static constexpr KeywordType type = KeywordType::Short;
    using Keyword::Keyword;
};

struct While : public Keyword<While> {
    static constexpr KeywordType type = KeywordType::While;
    using Keyword::Keyword;
};

struct Union : public Keyword<Union> {
    static constexpr KeywordType type = KeywordType::Union;
    using Keyword::Keyword;
};

struct Auto : public Keyword<Auto> {
    static constexpr KeywordType type = KeywordType::Auto;
    using Keyword::Keyword;
};

struct Case : public Keyword<Case> {
    static constexpr KeywordType type = KeywordType::Case;
    using Keyword::Keyword;
};

struct Char : public Keyword<Char> {
    static constexpr KeywordType type = KeywordType::Char;
    using Keyword::Keyword;
};

struct Else : public Keyword<Else> {
    static constexpr KeywordType type = KeywordType::Else;
    using Keyword::Keyword;
};

struct Enum : public Keyword<Enum> {
    static constexpr KeywordType type = KeywordType::Enum;
    using Keyword::Keyword;
};

struct Goto : public Keyword<Goto> {
    static constexpr KeywordType type = KeywordType::Goto;
    using Keyword::Keyword;
};

struct Long : public Keyword<Long> {
    static constexpr KeywordType type = KeywordType::Long;
    using Keyword::Keyword;
};

struct Void : public Keyword<Void> {
    static constexpr KeywordType type = KeywordType::Void;
    using Keyword::Keyword;
};

struct For : public Keyword<For> {
    static constexpr KeywordType type = KeywordType::For;
    using Keyword::Keyword;
};

struct Int : public Keyword<Int> {
    static constexpr KeywordType type = KeywordType::Int;
    using Keyword::Keyword;
};

struct Do : public Keyword<Do> {
    static constexpr KeywordType type = KeywordType::Do;
    using Keyword::Keyword;
};

struct If : public Keyword<If> {
    static constexpr KeywordType type = KeywordType::If;
    using Keyword::Keyword;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Keyword<T> &) {
    return os << "Keyword " << T::type, os;
}

}  // namespace cless::syntax::token

#endif
