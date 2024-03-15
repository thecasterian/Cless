#include "cless/syntax/token/identifier.h"

namespace cless::syntax::token {

Identifier::Identifier(
    std::string name,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : TokenBase(std::move(file), line_start, line_end, col_start, col_end), name(std::move(name)) {}

std::ostream &operator<<(std::ostream &os, const Identifier &identifier) {
    return os << "Identifier " << identifier.name;
}

}  // namespace cless::syntax::token
