#include <iostream>

#include "cless/core/print/ansi_escape.h"
#include "cless/front-end/lexer/lexer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << cless::core::print::Bold << "cless: " << cless::core::print::Red
                  << "error:" << cless::core::print::Reset << " no input file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    cless::fend::lexer::Lexer lexer(argv[1]);
    while (true) {
        auto token = lexer.next();
        for (const auto& msg : token.msg)
            std::cerr << msg << std::endl;
        if (token.error)
            return EXIT_FAILURE;
        if (not token.tok.has_value())
            break;
        std::cout << token.tok.value() << std::endl;
    }
}
