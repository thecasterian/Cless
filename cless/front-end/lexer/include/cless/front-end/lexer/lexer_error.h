#ifndef CLESS_FRONT_END_LEXER_LEXER_ERROR_H
#define CLESS_FRONT_END_LEXER_LEXER_ERROR_H

#include <string>
#include <string_view>

namespace cless::fend::lexer {

struct LexerError {
    std::string error_message;
    std::string_view error_source;
};

}

#endif
