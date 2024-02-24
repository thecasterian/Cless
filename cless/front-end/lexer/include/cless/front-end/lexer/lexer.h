#ifndef CLESS_FRONT_END_LEXER_LEXER_H
#define CLESS_FRONT_END_LEXER_LEXER_H

#include "cless/core/types/token.h"

namespace cless::fend::lexer {

class Lexer {
    std::string path_;
    std::string source;
    const char *ptr;
    std::size_t line, col;

public:
    Lexer(std::string path);

    std::optional<core::types::Token> next();

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
    std::optional<core::types::PreprocessingToken> nextPreprocessingToken();
    std::optional<core::types::HeaderName> getHeaderName();
    std::optional<core::types::Identifier> getIdentifier();
    std::optional<core::types::IntegerConstant> getIntegerConstant();
    std::optional<core::types::FloatingConstant> getFloatingConstant();
    std::optional<core::types::CharacterConstant> getCharacterConstant();
    std::optional<core::types::StringLiteral> getStringLiteral();
    std::optional<core::types::Punctuation> getPunctuation();
};

}  // namespace cless::fend::lexer

#endif
