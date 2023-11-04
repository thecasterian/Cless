#ifndef CLESS_FRONT_END_LEXER_IMPL_H
#define CLESS_FRONT_END_LEXER_IMPL_H

#include "cless/front-end/lexer/data.h"

namespace cless::fend::lexer::impl {

struct LexerReturn {
    using Result = core::types::MaybeEither<core::types::Token, LexerError>;

    Result result;
    std::string_view remainder;
};

LexerReturn keyword(std::string_view input);
LexerReturn punctuation(std::string_view input);
LexerReturn identifier(std::string_view input);
LexerReturn integerConstant(std::string_view input);
LexerReturn floatingConstant(std::string_view input);
LexerReturn characterConstant(std::string_view input);
LexerReturn stringLiteral(std::string_view input);

}  // namespace cless::fend::lexer::impl

#endif
