#ifndef CLESS_CORE_TYPES_MONADIC_H
#define CLESS_CORE_TYPES_MONADIC_H

#include <concepts>
#include <string>
#include <variant>

#include "cless/core/types/exception.h"

namespace cless::core::types {

// MaybeEither = Just ValueType | Nothing | Error ErrorType
template <typename ValueType, typename ErrorType>
    requires(not std::same_as<ValueType, ErrorType>)
class MaybeEither {
public:
    static MaybeEither<ValueType, ErrorType> just(const ValueType& value) {
        return MaybeEither<ValueType, ErrorType>(value);
    }

    static MaybeEither<ValueType, ErrorType> just(ValueType&& value) {
        return MaybeEither<ValueType, ErrorType>(std::move(value));
    }

    static MaybeEither<ValueType, ErrorType> nothing() { return MaybeEither<ValueType, ErrorType>(); }

    static MaybeEither<ValueType, ErrorType> error(const ErrorType& error) {
        return MaybeEither<ValueType, ErrorType>(error);
    }

    static MaybeEither<ValueType, ErrorType> error(ErrorType&& error) {
        return MaybeEither<ValueType, ErrorType>(std::move(error));
    }

    bool isJust() const { return std::holds_alternative<ValueType>(value); }
    bool isNothing() const { return std::holds_alternative<std::monostate>(value); }
    bool isError() const { return std::holds_alternative<ErrorType>(value); }

    ValueType getJust() const {
        if (isNothing())
            throw Exception("MaybeEither::getJust() called on Nothing");
        else if (isError())
            throw Exception("MaybeEither::getJust() called on Error");
        return std::get<ValueType>(value);
    }
    ErrorType getError() const {
        if (isJust())
            throw Exception("MaybeEither::getError() called on Just");
        else if (isNothing())
            throw Exception("MaybeEither::getError() called on Nothing");
        return std::get<ErrorType>(value);
    }

private:
    MaybeEither() : value(std::monostate()) {}
    MaybeEither(const ValueType& value) : value(value) {}
    MaybeEither(ValueType&& value) : value(std::move(value)) {}
    MaybeEither(const ErrorType& error) : value(error) {}
    MaybeEither(ErrorType&& error) : value(std::move(error)) {}

    std::variant<std::monostate, ValueType, ErrorType> value;
};

}  // namespace cless::core::types

#endif
