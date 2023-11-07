#ifndef CLESS_CORE_BASE_PRINT_H
#define CLESS_CORE_BASE_PRINT_H

#include <format>
#include <iostream>
#include <limits>
#include <string>

namespace cless::core::base::print {

struct AnsiEscapeCode {
    static constexpr std::size_t UNDEF = std::numeric_limits<std::size_t>::max();

    std::size_t mode = UNDEF;
    std::size_t foreground = UNDEF;
    std::size_t background = UNDEF;

    constexpr AnsiEscapeCode operator|(const AnsiEscapeCode& other) const {
        AnsiEscapeCode result;
        result.mode = (other.mode != UNDEF) ? other.mode : mode;
        result.foreground = (other.foreground != UNDEF) ? other.foreground : foreground;
        result.background = (other.background != UNDEF) ? other.background : background;
        return result;
    }

    constexpr operator std::string() const {
        std::string result = "\033[";
        if (mode != UNDEF) {
            result += std::to_string(mode);
            if (foreground != UNDEF or background != UNDEF) result += ";";
        }
        if (foreground != UNDEF) {
            result += std::to_string(foreground);
            if (background != UNDEF) result += ";";
        }
        if (background != UNDEF) {
            result += std::to_string(background);
        }
        result += "m";
        return result;
    }
};

std::ostream& operator<<(std::ostream& os, const cless::core::base::print::AnsiEscapeCode& code);

constexpr AnsiEscapeCode RESET = {.mode = 0};
constexpr AnsiEscapeCode BOLD = {.mode = 1};
constexpr AnsiEscapeCode ITALIC = {.mode = 3};
constexpr AnsiEscapeCode UNDERLINE = {.mode = 4};

constexpr AnsiEscapeCode BLACK = {.foreground = 30};
constexpr AnsiEscapeCode RED = {.foreground = 31};
constexpr AnsiEscapeCode GREEN = {.foreground = 32};
constexpr AnsiEscapeCode YELLOW = {.foreground = 33};
constexpr AnsiEscapeCode BLUE = {.foreground = 34};
constexpr AnsiEscapeCode MAGENTA = {.foreground = 35};
constexpr AnsiEscapeCode CYAN = {.foreground = 36};
constexpr AnsiEscapeCode WHITE = {.foreground = 37};

constexpr AnsiEscapeCode BRIGHT_BLACK = {.foreground = 90};
constexpr AnsiEscapeCode BRIGHT_RED = {.foreground = 91};
constexpr AnsiEscapeCode BRIGHT_GREEN = {.foreground = 92};
constexpr AnsiEscapeCode BRIGHT_YELLOW = {.foreground = 93};
constexpr AnsiEscapeCode BRIGHT_BLUE = {.foreground = 94};
constexpr AnsiEscapeCode BRIGHT_MAGENTA = {.foreground = 95};
constexpr AnsiEscapeCode BRIGHT_CYAN = {.foreground = 96};
constexpr AnsiEscapeCode BRIGHT_WHITE = {.foreground = 97};

}  // namespace cless::core::base::print

template <>
struct std::formatter<cless::core::base::print::AnsiEscapeCode> : public std::formatter<std::string> {
    auto format(const cless::core::base::print::AnsiEscapeCode& code, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}", static_cast<std::string>(code));
    }
};

#endif
