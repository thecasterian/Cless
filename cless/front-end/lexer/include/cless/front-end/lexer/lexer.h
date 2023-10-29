#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include <vector>

#include "cless/front-end/lexer/data.h"

namespace cless::fend::lexer {

core::types::MaybeEither<std::vector<core::types::Token>, LexerError> lex(std::string_view source);

}

#endif
