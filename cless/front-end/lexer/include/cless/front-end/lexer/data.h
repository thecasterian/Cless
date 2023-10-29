#ifndef CLESS_FRONT_END_LEXER_DATA_H
#define CLESS_FRONT_END_LEXER_DATA_H

#include <string>
#include <string_view>

#include "cless/core/types/monadic.h"
#include "cless/core/types/token.h"

namespace cless::fend::lexer {

struct LexerError {
    std::string msg;
    std::string_view str;
};

}

#endif
