#include "cless/front-end/lexer/lexer.h"

namespace cless::fend::lexer {
using core::types::MaybeEither;
using core::types::Token;

MaybeEither<std::vector<Token>, LexerError> lex(std::string_view source) {
    return MaybeEither<std::vector<Token>, LexerError>::error(LexerError{"Not implemented", source});
}

}  // namespace cless::fend::lexer
