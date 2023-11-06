#include <iostream>

#include "cless/front-end/file/file.h"
#include "cless/front-end/lexer/lexer.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::filesystem::path path = argv[1];
    cless::fend::file::File f(path);

    auto tokens = cless::fend::lexer::lex(f.getContents());
    if (not tokens.has_value()) {
        std::cerr << tokens.error().message << std::endl;
        return EXIT_FAILURE;
    }
}
