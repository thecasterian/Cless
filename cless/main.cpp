#include <iostream>

#include "cless/front-end/lexer/lexer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;
    }

    cless::fend::lexer::Lexer lexer(argv[1]);
    while (auto token = lexer.next()) {
        std::cout << token.value() << std::endl;
    }
}
