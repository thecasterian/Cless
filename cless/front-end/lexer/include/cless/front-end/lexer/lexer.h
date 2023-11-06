#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include <expected>
#include <vector>

#include "cless/core/types/token.h"
#include "cless/front-end/lexer/data.h"

namespace cless::fend::lexer {

std::expected<std::vector<core::types::Token>, LexerError> lex(std::string_view source);

}

#endif
