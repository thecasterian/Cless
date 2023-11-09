#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

using cless::core::types::Identifier;

TEST(cless_fend_lexer_identifier, alpha) {
    std::string source = "abcde";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<Identifier>(lexer_return.value().value().token);
    ASSERT_EQ(identifier.name, "abcde");
}

TEST(cless_fend_lexer_identifier, alphanum) {
    std::string source = "a1b2c3d4e5";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<Identifier>(lexer_return.value().value().token);
    ASSERT_EQ(identifier.name, "a1b2c3d4e5");
}

TEST(cless_fend_lexer_identifier, underscore) {
    std::string source = "_abcde_";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<Identifier>(lexer_return.value().value().token);
    ASSERT_EQ(identifier.name, "_abcde_");
}

TEST(cless_fend_lexer_identifier, dollar) {
    std::string source = "$ab$cde";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<Identifier>(lexer_return.value().value().token);
    ASSERT_EQ(identifier.name, "$ab$cde");
}

TEST(cless_fend_lexer_identifier, start_with_digit) {
    std::string source = "1abcde";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_identifier, following_token) {
    std::string source = "abcde 123 \"Hi\"";

    auto lexer_return = cless::fend::lexer::impl::identifier(source);
    auto remainder = lexer_return.value().value().remainder;
    ASSERT_EQ(remainder, " 123 \"Hi\"");
}
