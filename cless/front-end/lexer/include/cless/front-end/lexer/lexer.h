#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include <vector>

#include "cless/core/types/message.h"
#include "cless/syntax/token/token.h"

namespace cless::fend::lexer {

class Lexer {
    std::string path_;
    std::string source;
    const char *ptr;
    std::size_t line, col;

public:
    Lexer(std::string path);

    template <typename TokenType>
    struct Return {
        std::optional<TokenType> tok;
        std::vector<core::types::Message> msg;
        bool error;
    };

    Return<syntax::token::Token> next();

    const std::string &path() const;

private:
    void adv(std::size_t n = 1);
    char lookForward(std::size_t n = 1) const;

    struct Position {
        const char *ptr;
        std::size_t line, col;
    };

    Position tell() const;
    void seek(const Position &pos);

    void skipWhitespacesAndComments();
    Return<syntax::token::PreprocessingToken> nextPreprocessingToken();
    Return<syntax::token::PreprocessingToken> getHeaderName();
    Return<syntax::token::PreprocessingToken> getIdentifier();
    Return<syntax::token::PreprocessingToken> getIntegerConstant();
    Return<syntax::token::PreprocessingToken> getFloatingConstant();
    Return<syntax::token::PreprocessingToken> getCharacterConstant();
    Return<syntax::token::PreprocessingToken> getStringLiteral();
    Return<syntax::token::PreprocessingToken> getPunctuation();
};

}  // namespace cless::fend::lexer

#endif
