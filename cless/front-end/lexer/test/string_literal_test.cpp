#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

TEST(cless_fend_lexer_strlit, one_letter) {
    std::string source = "\"a\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "a");
}

TEST(cless_fend_lexer_strlit, multi_letters) {
    std::string source = "\"a9_\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "a9_");
}

TEST(cless_fend_lexer_strlit, simple_escape1) {
    std::string source = "\"\\n\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\n");
}

TEST(cless_fend_lexer_strlit, simple_escape2) {
    std::string source = "\"\\\"\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\\"");
}

TEST(cless_fend_lexer_strlit, octal_escape1) {
    std::string source = "\"\\0\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\0");
}

TEST(cless_fend_lexer_strlit, octal_escape2) {
    std::string source = "\"\\123\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\123");
}

TEST(cless_fend_lexer_strlit, hex_escape1) {
    std::string source = "\"\\x0\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\x0");
}

TEST(cless_fend_lexer_strlit, hex_escape2) {
    std::string source = "\"\\x42\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "\\x42");
}

TEST(cless_fend_lexer_strlit, missing_quote) {
    std::string source = "\"abcde";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_strlit, missing_quote2) {
    std::string source = "\"hi\\\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_strlit, missing_hex_escape) {
    std::string source = "\"\\xFF\\x\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_strlit, prefix_u8) {
    std::string source = "u8\"XYZ\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "XYZ");
    ASSERT_EQ(str_lit.prefix, cless::core::types::EncodingPrefix::UTF8);
}

TEST(cless_fend_lexer_strlit, prefix_L) {
    std::string source = "L\"XYZ\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "XYZ");
    ASSERT_EQ(str_lit.prefix, cless::core::types::EncodingPrefix::WChar);
}

TEST(cless_fend_lexer_strlit, prefix_u) {
    std::string source = "u\"A\\nB\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "A\\nB");
    ASSERT_EQ(str_lit.prefix, cless::core::types::EncodingPrefix::Char16);
}

TEST(cless_fend_lexer_strlit, prefix_U) {
    std::string source = "U\"%%\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    auto str_lit = std::get<cless::core::types::StringLiteral>(result.getJust());
    ASSERT_EQ(str_lit.value, "%%");
    ASSERT_EQ(str_lit.prefix, cless::core::types::EncodingPrefix::Char32);
}

TEST(cless_fend_lexer_strlit, prefix_wrong) {
    std::string source = "prefix\"STRING\"";

    auto [result, remaining] = cless::fend::lexer::impl::stringLiteral(source);
    ASSERT_FALSE(result.isJust());
}
