#ifndef CLESS_FRONT_END_LEXER_UTILS_H
#define CLESS_FRONT_END_LEXER_UTILS_H

#include <cctype>
#include <cstdint>
#include <optional>

namespace cless::fend::lexer::utils {

std::intmax_t charToInt(char c);

bool isIdentifierChar(char c);
bool isIdentifierStartChar(char c);

bool isHexBaseChar(char c);
bool hasBase(char curr, char next);

bool isOctDigit(char c);

bool isExponentChar(char c);
bool isSignChar(char c);
bool hasExponent(char curr, char next);

bool isSimpleEscapeChar(char c);

}  // namespace cless::fend::lexer::utils

#endif
