#include "cless/front-end/file/file.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "cless/core/types/exception.h"

namespace cless::fend::file {

File::File(const std::filesystem::path& path) : path(path) {
    // Read whole file contents
    std::ifstream ifs(path);
    if (ifs) {
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        contents = buffer.str();
    } else {
        throw core::types::Exception(std::format("Could not open file: {}", path.string()));
    }

    // Split into lines
    auto it = contents.begin();
    while (it != contents.end()) {
        std::string::iterator line_end = std::find(it, contents.end(), '\n');
        if (line_end != contents.end()) ++line_end;
        lines.push_back(std::string_view(it, line_end));
        it = line_end;
    }
}

const std::filesystem::path& File::getPath() const {
    return path;
}

const std::string& File::getContents() const {
    return contents;
}

std::size_t File::getNumLines() const {
    return lines.size();
}

std::string_view File::getLine(std::size_t line_number) const {
    return lines.at(line_number);
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
