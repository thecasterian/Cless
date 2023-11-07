#include "cless/core/base/print.h"

namespace cless::core::base::print {

std::ostream& operator<<(std::ostream& os, const cless::core::base::print::AnsiEscapeCode& code) {
    os << static_cast<std::string>(code);
    return os;
}

}  // namespace cless::core::base::print
