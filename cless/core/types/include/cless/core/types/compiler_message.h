#ifndef CLESS_CORE_TYPES_COMPILER_MESSAGE_H
#define CLESS_CORE_TYPES_COMPILER_MESSAGE_H

#include <string>
#include <string_view>
#include <vector>

namespace cless::core::types {

struct Note {
    std::string message;
    std::string_view source;
};

struct Error {
    std::string message;
    std::string_view source;
};

struct Warning {
    std::string message;
    std::string_view source;
};

}  // namespace cless::core::types

#endif
