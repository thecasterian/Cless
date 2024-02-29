#ifndef CLESS_CORE_TYPES_TOKENBASE_H
#define CLESS_CORE_TYPES_TOKENBASE_H

#include <string>

namespace cless::syntax::token {

struct TokenBase {
    std::string file;
    std::size_t line_start, line_end;
    std::size_t col_start, col_end;

    TokenBase(
        std::string file, std::size_t line_start, std::size_t line_end, std::size_t col_start, std::size_t col_end);
};

}  // namespace cless::syntax::token

#endif
