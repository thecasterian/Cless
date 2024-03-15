#include "cless/syntax/token/constant.h"

#include "cless/core/types/exception.h"

namespace cless::syntax::token {

std::ostream& operator<<(std::ostream& os, IntegerSuffix suffix) {
    switch (suffix) {
        case IntegerSuffix::None:
            return os << "", os;
        case IntegerSuffix::Unsigned:
            return os << "u", os;
        case IntegerSuffix::Long:
            return os << "l", os;
        case IntegerSuffix::UnsignedLong:
            return os << "ul", os;
        case IntegerSuffix::LongLong:
            return os << "ll", os;
        case IntegerSuffix::UnsignedLongLong:
            return os << "ull", os;
    }
    throw core::types::Exception("Unknown integer suffix");
}

std::optional<IntegerSuffix> integerSuffixFromStr(const std::string& str) {
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

IntegerConstant::IntegerConstant(
    std::intmax_t value,
    IntegerSuffix suffix,
    std::string source,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : Constant(std::move(file), line_start, line_end, col_start, col_end),
      value(value),
      suffix(suffix),
      source(std::move(source)) {}

std::ostream& operator<<(std::ostream& os, const IntegerConstant& constant) {
    return os << "IntegerConstant " << constant.source, os;
}

std::ostream& operator<<(std::ostream& os, FloatingSuffix suffix) {
    switch (suffix) {
        case FloatingSuffix::None:
            return os << "", os;
        case FloatingSuffix::Float:
            return os << "f", os;
        case FloatingSuffix::LongDouble:
            return os << "l", os;
    }
    throw core::types::Exception("Unknown floating suffix");
}

std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string& str) {
    if (str == "")
        return FloatingSuffix::None;
    else if (str == "f" or str == "F")
        return FloatingSuffix::Float;
    else if (str == "l" or str == "L")
        return FloatingSuffix::LongDouble;
    else
        return std::nullopt;
}

FloatingConstant::FloatingConstant(
    long double value,
    FloatingSuffix suffix,
    std::string source,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : Constant(std::move(file), line_start, line_end, col_start, col_end),
      value(value),
      suffix(suffix),
      source(std::move(source)) {}

std::ostream& operator<<(std::ostream& os, const FloatingConstant& constant) {
    return os << "FloatingConstant " << constant.source, os;
}

CharacterConstant::CharacterConstant(
    std::intmax_t value,
    std::string source,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : Constant(std::move(file), line_start, line_end, col_start, col_end), value(value), source(std::move(source)) {}

std::ostream& operator<<(std::ostream& os, const CharacterConstant& constant) {
    return os << "CharacterConstant '" << constant.source << "'", os;
}

}  // namespace cless::syntax::token
