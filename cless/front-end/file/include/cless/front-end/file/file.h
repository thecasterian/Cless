#ifndef CLESS_FRONT_END_FILE_FILE_H
#define CLESS_FRONT_END_FILE_FILE_H

#include <string>
#include <string_view>
#include <vector>

namespace cless::fend::file {

class File {
public:
    File(const std::string& path);
    ~File() = default;

    const std::string& getPath() const;
    const std::string& getContents() const;

    std::string::iterator begin();
    std::string::iterator end();
    std::string::const_iterator begin() const;
    std::string::const_iterator end() const;

private:
    std::string path;
    std::string contents;
    std::vector<std::string_view> lines;
};

}  // namespace cless::fend::file

#endif
