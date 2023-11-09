#include <gtest/gtest.h>

#include "cless/front-end/lexer/impl.h"

using cless::core::types::IntegerConstant;

TEST(cless_fend_lexer_intconst, dec) {
    std::string source = "12345";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<IntegerConstant>(lexer_return.value().value().token);
    ASSERT_EQ(int_const.value, "12345");
}

TEST(cless_fend_lexer_intconst, oct) {
    std::string source = "012345";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<IntegerConstant>(lexer_return.value().value().token);
    ASSERT_EQ(int_const.value, "012345");
}

TEST(cless_fend_lexer_intconst, hex) {
    std::string source = "0x129ABF";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<IntegerConstant>(lexer_return.value().value().token);
    ASSERT_EQ(int_const.value, "0x129ABF");
}

TEST(cless_fend_lexer_intconst, oct_8) {
    std::string source = "01248567";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_intconst, oct_9) {
    std::string source = "01245697";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_intconst, suffix_l) {
    std::string source = "12345L";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<IntegerConstant>(lexer_return.value().value().token);
    ASSERT_EQ(int_const.value, "12345");
    ASSERT_EQ(int_const.suffix, cless::core::types::IntegerSuffix::Long);
}

TEST(cless_fend_lexer_intconst, suffix_ull) {
    std::string source = "12345llU";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto int_const = std::get<IntegerConstant>(lexer_return.value().value().token);
    ASSERT_EQ(int_const.value, "12345");
    ASSERT_EQ(int_const.suffix, cless::core::types::IntegerSuffix::UnsignedLongLong);
}

TEST(cless_fend_lexer_intconst, suffix_wrong) {
    std::string source = "0X12345_wrong_suffix";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    ASSERT_FALSE(lexer_return.has_value() and lexer_return.value().has_value());
}

TEST(cless_fend_lexer_intconst, following_token) {
    std::string source = "0xFFull 'a' int";

    auto lexer_return = cless::fend::lexer::impl::integerConstant(source);
    auto remainder = lexer_return.value().value().remainder;
    ASSERT_EQ(remainder, " 'a' int");
}
