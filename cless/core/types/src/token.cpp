#include "cless-core/types/token.h"

namespace cless::core::types {

std::string to_string(const Token& token) {
    // TODO: implement
    return "";
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << to_string(token);
    return os;
}

}  // namespace cless::core::types
