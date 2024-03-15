#include "cless/syntax/token/string_literal.h"

namespace cless::syntax::token {

StringLiteral::StringLiteral(
    std::string value,
    std::string source,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : TokenBase(std::move(file), line_start, line_end, col_start, col_end),
      value(std::move(value)),
      source(std::move(source)) {}

std::ostream &operator<<(std::ostream &os, const StringLiteral &literal) {
    return os << "StringLiteral \"" << literal.source << "\"", os;
}

}  // namespace cless::syntax::token
