#include "cless/syntax/token/tokenbase.h"

namespace cless::syntax::token {

TokenBase::TokenBase(
    std::string file, std::size_t line_start, std::size_t line_end, std::size_t col_start, std::size_t col_end)
    : file(std::move(file)), line_start(line_start), line_end(line_end), col_start(col_start), col_end(col_end) {}

}  // namespace cless::syntax::token
