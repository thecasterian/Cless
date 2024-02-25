#include "cless/front-end/lexer/utils.h"

#include "cless/core/types/exception.h"

namespace cless::fend::lexer::utils {

std::intmax_t charToInt(char c) {
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
    }

    throw core::types::Exception("Invalid digit");
}

bool isEndOfLineChar(char c) {
    return c == '\n' or c == '\0';
}

bool isIdentifierChar(char c) {
    return std::isalnum(c) or c == '_';
}

bool isIdentifierStartChar(char c) {
    return std::isalpha(c) or c == '_';
}

bool isHexBaseChar(char c) {
    return c == 'x' or c == 'X';
}

bool hasBase(char curr, char next) {
    return curr == '0' and (isHexBaseChar(next) or std::isdigit(next));
}

bool isOctDigit(char c) {
    return std::isdigit(c) and c != '8' and c != '9';
}

bool isExponentChar(char c) {
    return c == 'e' or c == 'E';
}

bool isSignChar(char c) {
    return c == '+' or c == '-';
}

bool hasExponent(char curr, char next) {
    return isExponentChar(curr) and (isSignChar(next) or std::isdigit(next));
}

bool isSimpleEscapeChar(char c) {
    switch (c) {
        case '\'':
        case '"':
        case '?':
        case '\\':
        case 'a':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
            return true;
        default:
            return false;
    }
}

}  // namespace cless::fend::lexer::utils
