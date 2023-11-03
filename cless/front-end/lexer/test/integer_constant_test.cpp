#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

TEST(cless_fend_lexer_intconst, dec) {
    std::string source = "12345";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<cless::core::types::IntegerConstant>(result.getJust());
    ASSERT_EQ(int_const.value, "12345");
}

TEST(cless_fend_lexer_intconst, oct) {
    std::string source = "012345";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<cless::core::types::IntegerConstant>(result.getJust());
    ASSERT_EQ(int_const.value, "012345");
}

TEST(cless_fend_lexer_intconst, hex) {
    std::string source = "0x129ABF";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<cless::core::types::IntegerConstant>(result.getJust());
    ASSERT_EQ(int_const.value, "0x129ABF");
}

TEST(cless_fend_lexer_intconst, oct_8) {
    std::string source = "01248567";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_intconst, oct_9) {
    std::string source = "01245697";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_intconst, suffix_l) {
    std::string source = "12345L";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<cless::core::types::IntegerConstant>(result.getJust());
    ASSERT_EQ(int_const.value, "12345");
    ASSERT_EQ(int_const.suffix, cless::core::types::IntegerSuffix::Long);
}

TEST(cless_fend_lexer_intconst, suffix_ull) {
    std::string source = "12345llU";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<cless::core::types::IntegerConstant>(result.getJust());
    ASSERT_EQ(int_const.value, "12345");
    ASSERT_EQ(int_const.suffix, cless::core::types::IntegerSuffix::UnsignedLongLong);
}

TEST(cless_fend_lexer_intconst, suffix_wrong) {
    std::string source = "12345_wrong_suffix";

    auto [result, remaining] = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(result.isJust());
}
