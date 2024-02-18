#include "cless/core/types/exception.h"

namespace cless::core::types {

Exception::Exception(const std::string& message) : message(message) {}

Exception::~Exception() throw() {}

const char* Exception::what() const throw() {
    return message.c_str();
}

}  // namespace cless::core::types
