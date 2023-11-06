#ifndef CLESS_FRONT_END_LEXER_DATA_H
#define CLESS_FRONT_END_LEXER_DATA_H

#include <string>
#include <string_view>

namespace cless::fend::lexer {

struct LexerError {
    std::string message;
    std::string_view source;
};

}

#endif
