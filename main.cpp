#include <iostream>

#include "cless-core/types/token.h"

using cless::core::types::operator<<;

int main(void) {
    cless::core::types::Token x = cless::core::types::token::keyword::Const{};
    std::cout << x << std::endl;
}
