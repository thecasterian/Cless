#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

using cless::core::types::FloatingConstant;

TEST(cless_fend_lexer_floatconst, dec_simple) {
    std::string source = "12345.6789";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.6789");
}

TEST(cless_fend_lexer_floatconst, dec_no_int) {
    std::string source = ".6789";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, ".6789");
}

TEST(cless_fend_lexer_floatconst, dec_no_frac) {
    std::string source = "12345.";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.");
}

TEST(cless_fend_lexer_floatconst, dec_exp) {
    std::string source = "12345.6789e10";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.6789e10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_sign) {
    std::string source = "12345.6789e+10";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.6789e+10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_frac) {
    std::string source = "12345.E10";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.E10");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_int) {
    std::string source = ".6789E-9";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, ".6789E-9");
}

TEST(cless_fend_lexer_floatconst, dec_exp_no_dot) {
    std::string source = "12345e0";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345e0");
}

TEST(cless_fend_lexer_floatconst, dec_no_dot_exp) {
    std::string source = "12345";  // integer

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, dec_exp_missing) {
    std::string source = "12345e";  // integer with suffix "e"

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, no_int_frac) {
    std::string source = ".e5";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, hex_simple) {
    std::string source = "0x1.Fp5";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "0x1.Fp5");
}

TEST(cless_fend_lexer_floatconst, hex_no_int) {
    std::string source = "0X.FP5";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "0X.FP5");
}

TEST(cless_fend_lexer_floatconst, hex_no_frac) {
    std::string source = "0x1P7";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "0x1P7");
}

TEST(cless_fend_lexer_floatconst, hex_exp_sign) {
    std::string source = "0x1.fp+5";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
}

TEST(cless_fend_lexer_floatconst, hex_exp_missing_1) {
    std::string source = "0x12.3eAF";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, hex_exp_missing_2) {
    std::string source = "0x12.3eAFp";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, suffix_f) {
    std::string source = "12345.6789f";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "12345.6789");
    ASSERT_EQ(float_const.suffix, cless::core::types::FloatingSuffix::Float);
}

TEST(cless_fend_lexer_floatconst, suffix_l) {
    std::string source = "13.45e+7L";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto float_const = std::get<FloatingConstant>(lexer_return.value().value().token);
    ASSERT_EQ(float_const.value, "13.45e+7");
    ASSERT_EQ(float_const.suffix, cless::core::types::FloatingSuffix::LongDouble);
}

TEST(cless_fend_lexer_floatconst, suffix_wrong) {
    std::string source = "0x125.679e+7KLM";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_floatconst, following_token) {
    std::string source = "1.5e+3 abc 0xFF";

    auto lexer_return = cless::fend::lexer::impl::floatingConstant(source);
    auto remainder = lexer_return.value().value().remainder;
    ASSERT_EQ(remainder, " abc 0xFF");
}
