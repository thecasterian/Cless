#include "cless/front-end/lexer/lexer.h"

#include <gtest/gtest.h>

#include "cless/configure/configure.h"
#include "cless/front-end/file/file.h"

using cless::configure::root_path;
using cless::core::types::TokenType;
using cless::fend::file::File;

TEST(cless_front_end_lexer, empty_file) {
    std::filesystem::path path = root_path / "test-data/empty_file.c";
    File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents()).getJust();

    ASSERT_TRUE(tokens.empty());
}

TEST(cless_front_end_lexer, empty_main) {
    std::filesystem::path path = root_path / "test-data/empty_main.c";
    File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents()).getJust();

    ASSERT_EQ(tokens.size(), 7);
    ASSERT_EQ(tokens.at(0).type, TokenType::Int);
    ASSERT_EQ(tokens.at(1).type, TokenType::Identifier);
    ASSERT_EQ(tokens.at(1).str, "main");
    ASSERT_EQ(tokens.at(2).type, TokenType::OpenParenthesis);
    ASSERT_EQ(tokens.at(3).type, TokenType::Void);
    ASSERT_EQ(tokens.at(4).type, TokenType::CloseParenthesis);
    ASSERT_EQ(tokens.at(5).type, TokenType::OpenBrace);
    ASSERT_EQ(tokens.at(6).type, TokenType::CloseBrace);
}

TEST(cless_front_end_lexer, integer_constant) {
    std::filesystem::path path = root_path / "test-data/integer_constant.c";
    File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents()).getJust();

    ASSERT_EQ(tokens.at(6).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(6).str, "0");

    ASSERT_EQ(tokens.at(8).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(8).str, "1u");

    ASSERT_EQ(tokens.at(10).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(10).str, "2llU");

    ASSERT_EQ(tokens.at(12).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(12).str, "0x3l");

    ASSERT_EQ(tokens.at(14).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(14).str, "0X4ULL");

    ASSERT_EQ(tokens.at(16).type, TokenType::IntegerConstant);
    ASSERT_EQ(tokens.at(16).str, "056");
}
