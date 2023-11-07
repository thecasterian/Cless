#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include <expected>
#include <vector>

#include "cless/core/types/compiler_message.h"
#include "cless/core/types/token.h"

namespace cless::fend::lexer {

std::expected<std::vector<core::types::Token>, core::types::Error> lex(std::string_view source);

}

#endif
