#include "cless/core/types/message.h"

#include "cless/core/print/ansi_escape.h"

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
    os << print::Bold << msg.file << ":" << msg.line << ":" << msg.column << ": ";
    switch (msg.type) {
        case Message::Type::Note:
            os << print::Cyan << "note:";
            break;
        case Message::Type::Warning:
            os << print::Magenta << "warning:";
            break;
        case Message::Type::Error:
            os << print::Red << "error:";
            break;
    }
    os << print::Reset << " " << msg.message;
    return os;
}

}  // namespace cless::core::types
