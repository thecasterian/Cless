#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

TEST(cless_fend_lexer_floatconst, dec_simple) {
    std::string source = "12345.6789";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.6789");
}

TEST(cless_fend_lexer_floatconst, dec_no_int) {
    std::string source = ".6789";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, ".6789");
}

TEST(cless_fend_lexer_floatconst, dec_no_frac) {
    std::string source = "12345.";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.");
}

TEST(cless_fend_lexer_floatconst, dec_exp) {
    std::string source = "12345.6789e10";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.6789e10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_sign) {
    std::string source = "12345.6789e+10";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.6789e+10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_frac) {
    std::string source = "12345.E10";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.E10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_int) {
    std::string source = ".6789E-9";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, ".6789E-9");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_dot) {
    std::string source = "12345e0";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345e0");
}

TEST(cless_fend_lexer_floatconst, dec_no_dot_exp) {
    std::string source = "12345";  // integer

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_floatconst, dec_exp_missing) {
    std::string source = "12345e";  // integer with suffix "e"

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_floatconst, no_int_frac) {
    std::string source = ".e5";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_floatconst, hex_simple) {
    std::string source = "0x1.Fp5";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "0x1.Fp5");
}

TEST(cless_fend_lexer_floatconst, hex_no_int) {
    std::string source = "0X.FP5";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "0X.FP5");
}

TEST(cless_fend_lexer_floatconst, hex_no_frac) {
    std::string source = "0x1P7";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "0x1P7");
}

TEST(cless_fend_lexer_floatconst, hex_exp_sign) {
    std::string source = "0x1.fp+5";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
}

TEST(cless_fend_lexer_floatconst, hex_exp_missing_1) {
    std::string source = "0x12.3eAF";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_floatconst, hex_exp_missing_2) {
    std::string source = "0x12.3eAFp";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(result.isJust());
}

TEST(cless_fend_lexer_floatconst, suffix_f) {
    std::string source = "12345.6789f";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "12345.6789");
    ASSERT_EQ(float_const.suffix, cless::core::types::FloatingSuffix::Float);
}

TEST(cless_fend_lexer_floatconst, suffix_l) {
    std::string source = "13.45e+7L";

    auto [result, remaining] = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<cless::core::types::FloatingConstant>(result.getJust());
    ASSERT_EQ(float_const.value, "13.45e+7");
    ASSERT_EQ(float_const.suffix, cless::core::types::FloatingSuffix::LongDouble);
}
