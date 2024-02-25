#include "cless/core/types/message.h"

namespace cless::core::types {

Message Message::note(std::string file, std::size_t line, std::size_t column, std::string message) {
    return {Type::Note, std::move(file), line, column, std::move(message)};
}

Message Message::warning(std::string file, std::size_t line, std::size_t column, std::string message) {
    return {Type::Warning, std::move(file), line, column, std::move(message)};
}

Message Message::error(std::string file, std::size_t line, std::size_t column, std::string message) {
    return {Type::Error, std::move(file), line, column, std::move(message)};
}

std::ostream &operator<<(std::ostream &os, const Message &msg) {
    os << "\033[1m" << msg.file << ":" << msg.line << ":" << msg.column << ": ";
    switch (msg.type) {
        case Message::Type::Note:
            os << "\033[1;34mnote: \033[0m";
            break;
        case Message::Type::Warning:
            os << "\033[1;35mwarning: \033[0m";
            break;
        case Message::Type::Error:
            os << "\033[1;31merror: \033[0m";
            break;
    }
    os << msg.message;
    return os;
}

}  // namespace cless::core::types
