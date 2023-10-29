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

TEST(cless_front_end_lexer, floating_constant) {
    std::filesystem::path path = root_path / "test-data/floating_constant.c";
    File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents()).getJust();

    ASSERT_EQ(tokens.at(6).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(6).str, "0.");

    ASSERT_EQ(tokens.at(8).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(8).str, ".1f");

    ASSERT_EQ(tokens.at(10).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(10).str, "23.7145F");

    ASSERT_EQ(tokens.at(12).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(12).str, "1e3L");

    ASSERT_EQ(tokens.at(14).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(14).str, ".53E+47l");

    ASSERT_EQ(tokens.at(16).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(16).str, "6.e-18");

    ASSERT_EQ(tokens.at(18).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(18).str, "0xB51.fa3Fd9ep+17f");

    ASSERT_EQ(tokens.at(20).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(20).str, "0x25P-126");

    ASSERT_EQ(tokens.at(22).type, TokenType::FloatingConstant);
    ASSERT_EQ(tokens.at(22).str, "0x1p1l");
}

TEST(cless_front_end_lexer, character_constant) {
    std::filesystem::path path = root_path / "test-data/character_constant.c";
    File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents()).getJust();

    ASSERT_EQ(tokens.at(6).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(6).str, "'a'");

    ASSERT_EQ(tokens.at(8).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(8).str, "'\\b'");

    ASSERT_EQ(tokens.at(10).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(10).str, "'a\\n\\tF\\v'");

    ASSERT_EQ(tokens.at(12).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(12).str, "'\\0'");

    ASSERT_EQ(tokens.at(14).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(14).str, "'x\\x012'");

    ASSERT_EQ(tokens.at(16).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(16).str, "'\\5379'");

    ASSERT_EQ(tokens.at(18).type, TokenType::CharacterConstant);
    ASSERT_EQ(tokens.at(18).str, "'\\'\\\"\"?\"\\\'\\?\\\\'");
}
