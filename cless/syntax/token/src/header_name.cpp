#include "cless/syntax/token/header_name.h"

namespace cless::syntax::token {

HeaderName::HeaderName(
    std::string name,
    bool is_system,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end)
    : TokenBase(file, line_start, line_end, col_start, col_end), name(name), is_system(is_system) {}

std::ostream& operator<<(std::ostream& os, const HeaderName& header_name) {
    return os << "HeaderName " << (header_name.is_system ? "<" : "\"") << header_name.name
              << (header_name.is_system ? ">" : "\""),
           os;
}

}  // namespace cless::syntax::token
