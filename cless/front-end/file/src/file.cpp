#include "cless/front-end/file/file.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <sstream>

#include "cless/core/base/print.h"
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
        lines.push_back(std::string_view(it, line_end));
        if (line_end != contents.end()) ++line_end;
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

static std::string positionMessage(
    const std::string& path,
    std::size_t line_number,
    std::size_t column_number,
    const std::string& type,
    const core::base::print::AnsiEscapeCode& type_code,
    const std::string& message) {
    return std::format(
        "{}{}:{}:{}:{} {}{}:{} {}",
        core::base::print::BOLD,
        path,
        line_number,
        column_number,
        core::base::print::RESET,
        type_code,
        type,
        core::base::print::RESET,
        message);
}

static std::string sourceMessage(
    std::size_t line_number,
    std::string_view line,
    std::string_view source,
    const core::base::print::AnsiEscapeCode& type_code) {
    std::ostringstream oss;
    return std::format(
        "{:5d} | {}{}{}{}{}\n      | {}{}^{}{}",
        line_number,
        std::string_view(line.begin(), source.begin()),
        type_code,
        source,
        core::base::print::RESET,
        std::string_view(source.end(), line.end()),
        std::string(source.begin() - line.begin(), ' '),
        type_code,
        std::string(source.size() - 1, '~'),
        core::base::print::RESET);
}

std::string File::compilerMessageString(const core::types::Note& note) const {
    std::size_t line_number = getLineNumber(note.source);
    auto line = getLine(line_number);
    std::size_t column_number = note.source.begin() - line.begin();

    auto pos_msg = positionMessage(
        path.string(), line_number + 1, column_number + 1, "note", core::base::print::BRIGHT_CYAN, note.message);
    auto src_msg = sourceMessage(line_number + 1, line, note.source, core::base::print::BRIGHT_CYAN);
    return std::format("{}\n{}", pos_msg, src_msg);
}

std::string File::compilerMessageString(const core::types::Error& error) const {
    std::size_t line_number = getLineNumber(error.source);
    auto line = getLine(line_number);
    std::size_t column_number = error.source.begin() - line.begin();

    auto pos_msg = positionMessage(
        path.string(), line_number + 1, column_number + 1, "error", core::base::print::BRIGHT_RED, error.message);
    auto src_msg = sourceMessage(line_number + 1, line, error.source, core::base::print::BRIGHT_RED);
    return std::format("{}\n{}", pos_msg, src_msg);
}

std::string File::compilerMessageString(const core::types::Warning& warning) const {
    std::size_t line_number = getLineNumber(warning.source);
    auto line = getLine(line_number);
    std::size_t column_number = warning.source.begin() - line.begin();

    auto pos_msg = positionMessage(
        path.string(),
        line_number + 1,
        column_number + 1,
        "warning",
        core::base::print::BRIGHT_YELLOW,
        warning.message);
    auto src_msg = sourceMessage(line_number + 1, line, warning.source, core::base::print::BRIGHT_YELLOW);
    return std::format("{}\n{}", pos_msg, src_msg);
}

std::size_t File::getLineNumber(std::string_view source) const {
    auto it = std::upper_bound(
                  lines.begin(),
                  lines.end(),
                  source.begin(),
                  [](std::string_view line, std::string_view source) { return line.begin() < source.begin(); }) -
              1;
    if (it >= lines.end()) throw core::types::Exception("Could not find line number");
    return static_cast<std::size_t>(std::distance(lines.begin(), it));
}

}  // namespace cless::fend::file
