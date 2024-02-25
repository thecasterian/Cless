#ifndef CLESS_CORE_PRINT_ANSI_ESCAPE_H
#define CLESS_CORE_PRINT_ANSI_ESCAPE_H

#include <ostream>

namespace cless::core::print {

struct AnsiEscape {
    int code;
};

std::ostream &operator<<(std::ostream &os, const AnsiEscape &esc);

constexpr AnsiEscape Reset{0};
constexpr AnsiEscape Bold{1};
constexpr AnsiEscape Faint{2};
constexpr AnsiEscape Italic{3};
constexpr AnsiEscape Underline{4};
constexpr AnsiEscape Inverse{7};
constexpr AnsiEscape Strike{9};

constexpr AnsiEscape Black{30};
constexpr AnsiEscape Red{31};
constexpr AnsiEscape Green{32};
constexpr AnsiEscape Yellow{33};
constexpr AnsiEscape Blue{34};
constexpr AnsiEscape Magenta{35};
constexpr AnsiEscape Cyan{36};
constexpr AnsiEscape White{37};

}  // namespace cless::core::print

#endif
