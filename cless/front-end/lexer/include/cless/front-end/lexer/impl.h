#ifndef CLESS_FRONT_END_LEXER_IMPL_H
#define CLESS_FRONT_END_LEXER_IMPL_H

#include "cless/front-end/lexer/data.h"

namespace cless::fend::lexer::impl {

struct LexerReturn {
    using Result = core::types::MaybeEither<core::types::Token, LexerError>;

    Result result;
    std::string_view remainder;
};

LexerReturn keyword(std::string_view source);
LexerReturn punctuation(std::string_view source);
LexerReturn identifier(std::string_view source);
LexerReturn integerConstant(std::string_view source);
LexerReturn floatingConstant(std::string_view source);
LexerReturn characterConstant(std::string_view source);
LexerReturn stringLiteral(std::string_view source);

}  // namespace cless::fend::lexer::impl

#endif
