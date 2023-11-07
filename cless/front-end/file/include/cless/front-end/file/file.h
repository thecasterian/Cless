#ifndef CLESS_FRONT_END_FILE_FILE_H
#define CLESS_FRONT_END_FILE_FILE_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include "cless/core/types/compiler_message.h"

namespace cless::fend::file {

class File {
public:
    File(const std::filesystem::path& path);
    ~File() = default;

    const std::filesystem::path& getPath() const;
    const std::string& getContents() const;
    std::size_t getNumLines() const;
    std::string_view getLine(std::size_t line_number) const;

    std::string::iterator begin();
    std::string::iterator end();
    std::string::const_iterator begin() const;
    std::string::const_iterator end() const;

    std::string compilerMessageString(const core::types::Note& note) const;
    std::string compilerMessageString(const core::types::Error& error) const;
    std::string compilerMessageString(const core::types::Warning& warning) const;

private:
    std::filesystem::path path;
    std::string contents;
    std::vector<std::string_view> lines;

    std::size_t getLineNumber(std::string_view source) const;
};

}  // namespace cless::fend::file

#endif
