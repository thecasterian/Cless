#include "cless/core/types/token.h"

namespace cless::core::types {

std::string to_string(const Token& token) {
    return std::string(token.str);
}

std::ostream &operator<<(std::ostream &os, const Token& token) {
    return os << to_string(token);
}

}  // namespace cless::core::types
