#ifndef CLESS_CORE_SYNTAX_STRING_LITERAL_H
#define CLESS_CORE_SYNTAX_STRING_LITERAL_H

#include <iostream>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

struct StringLiteral : public TokenBase {
    std::string value;
    std::string source;

    StringLiteral(
        std::string value,
        std::string source,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream &operator<<(std::ostream &os, const StringLiteral &literal);

}  // namespace cless::syntax::token

#endif
