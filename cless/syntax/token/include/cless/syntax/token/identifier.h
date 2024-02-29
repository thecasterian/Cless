#ifndef CLESS_CORE_SYNTAX_IDENTIFIER_H
#define CLESS_CORE_SYNTAX_IDENTIFIER_H

#include <iostream>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

struct Identifier : public TokenBase {
    std::string name;

    Identifier(
        std::string name,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream &operator<<(std::ostream &os, const Identifier &identifier);

}  // namespace cless::syntax::token

#endif
