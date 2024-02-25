#ifndef CLESS_CORE_TYPES_MESSAGE_H
#define CLESS_CORE_TYPES_MESSAGE_H

#include <ostream>
#include <string>

namespace cless::core::types {

struct Message {
    enum class Type {
        Note,
        Warning,
        Error
    };

    Type type;
    std::string file;
    std::size_t line;
    std::size_t column;
    std::string message;

    static Message note(std::string file, std::size_t line, std::size_t column, std::string message);
    static Message warning(std::string file, std::size_t line, std::size_t column, std::string message);
    static Message error(std::string file, std::size_t line, std::size_t column, std::string message);
};

std::ostream &operator<<(std::ostream &os, const Message &msg);

}  // namespace cless::core::types

#endif
