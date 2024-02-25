#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include <vector>

#include "cless/core/types/message.h"
#include "cless/core/types/token.h"

namespace cless::fend::lexer {

class Lexer {
    std::string path_;
    std::string source;
    const char *ptr;
    std::size_t line, col;

public:
    Lexer(std::string path);

    template <typename T>
    struct Return {
        std::optional<T> ret;
        std::vector<core::types::Message> msg;
    };

    Return<core::types::Token> next();

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
    Return<core::types::PreprocessingToken> nextPreprocessingToken();
    Return<core::types::HeaderName> getHeaderName();
    Return<core::types::Identifier> getIdentifier();
    Return<core::types::IntegerConstant> getIntegerConstant();
    Return<core::types::FloatingConstant> getFloatingConstant();
    Return<core::types::CharacterConstant> getCharacterConstant();
    Return<core::types::StringLiteral> getStringLiteral();
    Return<core::types::Punctuation> getPunctuation();
};

}  // namespace cless::fend::lexer

#endif
