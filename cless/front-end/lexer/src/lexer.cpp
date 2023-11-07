#include "cless/front-end/lexer/lexer.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <functional>

#include "cless/front-end/lexer/impl.h"

namespace cless::fend::lexer {
using core::types::Error;
using core::types::Token;

static std::string_view discardWhiteSpaces(std::string_view source) {
    return std::string_view{std::find_if_not(source.begin(), source.end(), isspace), source.end()};
}

std::expected<std::vector<Token>, Error> lex(std::string_view source) {
    std::vector<Token> tokens;
    // order matters
    const std::vector<std::function<impl::LexerReturn(std::string_view)>> lexer_impls{
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
            auto lexer_return = lexer_impl(source);
            if (lexer_return.has_value()) {
                auto exp = lexer_return.value();
                if (exp.has_value()) {
                    auto [token, remainder] = exp.value();
                    success = true;
                    tokens.push_back(token);
                    source = discardWhiteSpaces(remainder);
                } else {
                    return std::unexpected(exp.error());
                }
            }
        }

        if (not success)
            return std::unexpected(Error{std::format("stray \"{}\"", source[0]), std::string_view{source.begin(), 1}});
    }

    return tokens;
}

}  // namespace cless::fend::lexer
