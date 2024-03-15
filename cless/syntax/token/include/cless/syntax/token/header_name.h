#ifndef CLESS_CORE_SYNTAX_HEADER_NAME_H
#define CLESS_CORE_SYNTAX_HEADER_NAME_H

#include <iostream>

#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

struct HeaderName : public TokenBase {
    std::string name;
    bool is_system;

    HeaderName(
        std::string name,
        bool is_system,
        std::string file,
        std::size_t line_start,
        std::size_t line_end,
        std::size_t col_start,
        std::size_t col_end);
};

std::ostream& operator<<(std::ostream& os, const HeaderName& header_name);

}  // namespace cless::syntax::token

#endif
