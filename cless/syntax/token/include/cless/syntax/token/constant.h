#ifndef CLESS_CORE_SYNTAX_CONSTANT_H
#define CLESS_CORE_SYNTAX_CONSTANT_H

#include <cstdint>
#include <iostream>
#include <optional>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

template <typename Derived>
struct Constant : public TokenBase {
    using TokenBase::TokenBase;
};

enum class IntegerSuffix {
    None,
    Unsigned,
    Long,
    UnsignedLong,
    LongLong,
    UnsignedLongLong,
};
std::ostream &operator<<(std::ostream &os, IntegerSuffix suffix);
std::optional<IntegerSuffix> integerSuffixFromStr(const std::string &str);

struct IntegerConstant : public Constant<IntegerConstant> {
    std::intmax_t value;
    IntegerSuffix suffix;
    std::string source;

    IntegerConstant(
        std::intmax_t value,
        IntegerSuffix suffix,
        std::string source,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream &operator<<(std::ostream &os, const IntegerConstant &constant);

enum class FloatingSuffix {
    None,
    Float,
    LongDouble,
};
std::ostream &operator<<(std::ostream &os, FloatingSuffix suffix);
std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string &str);

struct FloatingConstant : public Constant<FloatingConstant> {
    long double value;
    FloatingSuffix suffix;
    std::string source;

    FloatingConstant(
        long double value,
        FloatingSuffix suffix,
        std::string source,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream &operator<<(std::ostream &os, const FloatingConstant &constant);

struct CharacterConstant : public Constant<CharacterConstant> {
    std::intmax_t value;
    std::string source;

    CharacterConstant(
        std::intmax_t value,
        std::string source,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream &operator<<(std::ostream &os, const CharacterConstant &constant);

}  // namespace cless::syntax::token

#endif
