#include <iostream>

#include "cless-core/types/token.h"

using cless::core::types::to_string;

int main(void) {
    cless::core::types::Token x = cless::core::types::token::Identifier{"a"};
    std::cout << to_string(x) << std::endl;
}
