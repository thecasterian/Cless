#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

TEST(cless_fend_lexer_identifier, alpha) {
    std::string source = "abcde";

    auto [result, remaining] = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<cless::core::types::Identifier>(result.getJust());
    ASSERT_EQ(identifier.name, "abcde");
}

TEST(cless_fend_lexer_identifier, alphanum) {
    std::string source = "a1b2c3d4e5";

    auto [result, remaining] = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<cless::core::types::Identifier>(result.getJust());
    ASSERT_EQ(identifier.name, "a1b2c3d4e5");
}

TEST(cless_fend_lexer_identifier, underscore) {
    std::string source = "_abcde_";

    auto [result, remaining] = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<cless::core::types::Identifier>(result.getJust());
    ASSERT_EQ(identifier.name, "_abcde_");
}

TEST(cless_fend_lexer_identifier, dollar) {
    std::string source = "$ab$cde";

    auto [result, remaining] = cless::fend::lexer::impl::identifier(source);
    auto identifier = std::get<cless::core::types::Identifier>(result.getJust());
    ASSERT_EQ(identifier.name, "$ab$cde");
}

TEST(cless_fend_lexer_identifier, start_with_digit) {
    std::string source = "1abcde";

    auto [result, remaining] = cless::fend::lexer::impl::identifier(source);
    ASSERT_FALSE(result.isJust());
}
