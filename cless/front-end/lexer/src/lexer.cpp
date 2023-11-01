#include "cless/front-end/lexer/lexer.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <functional>

#include "cless/front-end/lexer/impl.h"

namespace cless::fend::lexer {
using core::types::MaybeEither;
using core::types::Token;

static std::string_view discardWhiteSpaces(std::string_view source) {
    return std::string_view{std::find_if_not(source.begin(), source.end(), isspace), source.end()};
}

MaybeEither<std::vector<Token>, LexerError> lex(std::string_view source) {
    std::vector<Token> tokens;
    // order matters
    std::vector<std::function<impl::LexerReturn(std::string_view)>> lexer_impls{
        impl::characterConstant,
        impl::stringLiteral,
        impl::keyword,
        impl::identifier,
        impl::floatingConstant,
        impl::integerConstant,
        impl::punctuation,
    };

    source = discardWhiteSpaces(source);

    while (not source.empty()) {
        bool success = false;

        for (auto lexer_impl : lexer_impls) {
            auto [result, remainder] = lexer_impl(source);
            if (result.isJust()) {
                success = true;
                tokens.push_back(result.getJust());
                source = discardWhiteSpaces(remainder);
                break;
            } else if (result.isError()) {
                return MaybeEither<std::vector<Token>, LexerError>::error(result.getError());
            }
        }

        if (not success)
            return MaybeEither<std::vector<Token>, LexerError>::error(
                LexerError{std::format("stray \"{}\"", source[0]), std::string_view{source.begin(), 1}});
    }

    return MaybeEither<std::vector<Token>, LexerError>::just(std::move(tokens));
}

}  // namespace cless::fend::lexer
