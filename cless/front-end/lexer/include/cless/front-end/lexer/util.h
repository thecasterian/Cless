#ifndef CLESS_FRONT_END_LEXER_UTIL_H
#define CLESS_FRONT_END_LEXER_UTIL_H

#include "cless/core/types/monadic.h"
#include "cless/core/types/token.h"
#include "cless/front-end/lexer/lexer_error.h"

namespace cless::fend::lexer::util {

struct LexReturn {
    core::types::MaybeEither<core::types::Token, LexerError> result;
    std::string_view remainder;
};

}  // namespace cless::fend::lexer::util

#endif
