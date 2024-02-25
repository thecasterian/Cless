#include "cless/core/print/ansi_escape.h"

namespace cless::core::print {

std::ostream &operator<<(std::ostream &os, const AnsiEscape &esc) {
    os << "\033[" << esc.code << "m";
    return os;
}

}  // namespace cless::core::print
