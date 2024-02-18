#ifndef CLESS_CORE_TYPES_EXCEPTION_H
#define CLESS_CORE_TYPES_EXCEPTION_H

#include <exception>
#include <string>

namespace cless::core::types {

class Exception : public std::exception {
public:
    Exception(const std::string& message);
    virtual ~Exception() throw();
    virtual const char* what() const throw() override;

private:
    std::string message;
};

}  // namespace cless::core::types

#endif
