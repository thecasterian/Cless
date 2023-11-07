#ifndef CLESS_FRONT_END_LEXER_IMPL_H
#define CLESS_FRONT_END_LEXER_IMPL_H

#include <expected>
#include <optional>

#include "cless/core/types/compiler_message.h"
#include "cless/core/types/token.h"

namespace cless::fend::lexer::impl {

struct LexerResult {
    core::types::Token token;
    std::string_view remainder;
};

using LexerReturn = std::optional<std::expected<LexerResult, core::types::Error>>;

LexerReturn keyword(std::string_view input);
LexerReturn punctuation(std::string_view input);
LexerReturn identifier(std::string_view input);
LexerReturn integerConstant(std::string_view input);
LexerReturn floatingConstant(std::string_view input);
LexerReturn characterConstant(std::string_view input);
LexerReturn stringLiteral(std::string_view input);

}  // namespace cless::fend::lexer::impl

#endif
