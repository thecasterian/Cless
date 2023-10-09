#include "cless/front-end/file/file.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace cless::fend::file {

File::File(const std::string& path) : path(path) {
    // Read whole file contents
    std::ifstream ifs(path);
    if (ifs) {
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        contents = buffer.str();
    }
    // TODO: throw exception if file does not exist

    // Split into lines
    auto it = contents.begin();
    while (it != contents.end()) {
        std::string::iterator line_end = std::find(it, contents.end(), '\n');
        if (line_end != contents.end()) ++line_end;
        lines.push_back(std::string_view(it, line_end));
        it = line_end;
    }
}

const std::string& File::getPath() const {
    return path;
}

const std::string& File::getContents() const {
    return contents;
}

std::string::iterator File::begin() {
    return contents.begin();
}

std::string::iterator File::end() {
    return contents.end();
}

std::string::const_iterator File::begin() const {
    return contents.begin();
}

std::string::const_iterator File::end() const {
    return contents.end();
}

}  // namespace cless::fend::file
