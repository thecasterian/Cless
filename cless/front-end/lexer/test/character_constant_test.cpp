#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

using cless::core::types::CharacterConstant;

TEST(cless_fend_lexer_charconst, one_letter) {
    std::string source = "'a'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "a");
}

TEST(cless_fend_lexer_charconst, multi_letters) {
    std::string source = "'a9_'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "a9_");
}

TEST(cless_fend_lexer_charconst, simple_escape1) {
    std::string source = "'\\n'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\n");
}

TEST(cless_fend_lexer_charconst, simple_escape2) {
    std::string source = "'\\''";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\'");
}

TEST(cless_fend_lexer_charconst, octal_escape1) {
    std::string source = "'\\0'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\0");
}

TEST(cless_fend_lexer_charconst, octal_escape2) {
    std::string source = "'\\123'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\123");
}

TEST(cless_fend_lexer_charconst, hex_escape1) {
    std::string source = "'\\x0'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\x0");
}

TEST(cless_fend_lexer_charconst, hex_escape2) {
    std::string source = "'\\x42'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\x42");
}

TEST(cless_fend_lexer_charconst, missing_quote) {
    std::string source = "'a";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_charconst, missing_quote2) {
    std::string source = "'a\\'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_charconst, missing_hex_escape) {
    std::string source = "'\\x'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_charconst, prefix_u8) {
    std::string source = "u8'a'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "a");
    ASSERT_EQ(char_const.prefix, cless::core::types::EncodingPrefix::UTF8);
}

TEST(cless_fend_lexer_charconst, prefix_L) {
    std::string source = "L'T'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "T");
    ASSERT_EQ(char_const.prefix, cless::core::types::EncodingPrefix::WChar);
}

TEST(cless_fend_lexer_charconst, prefix_u) {
    std::string source = "u'\\t'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "\\t");
    ASSERT_EQ(char_const.prefix, cless::core::types::EncodingPrefix::Char16);
}

TEST(cless_fend_lexer_charconst, prefix_U) {
    std::string source = "U'@'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    auto char_const = std::get<CharacterConstant>(lexer_return.value().value().token);
    ASSERT_EQ(char_const.value, "@");
    ASSERT_EQ(char_const.prefix, cless::core::types::EncodingPrefix::Char32);
}

TEST(cless_fend_lexer_charconst, prefix_wrong) {
    std::string source = "prefix'a'";

    auto lexer_return = cless::fend::lexer::impl::characterConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}
