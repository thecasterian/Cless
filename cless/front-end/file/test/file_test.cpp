#include "cless/front-end/file/file.h"

#include <gtest/gtest.h>

#include "cless/configure/configure.h"
#include "cless/core/types/exception.h"

using cless::configure::root_path;
using cless::fend::file::File;

TEST(cless_fend_file, not_exist) {
    std::filesystem::path path = root_path / "test-data/not_exist.c";

    ASSERT_THROW({ File f(path); }, cless::core::types::Exception);
}

TEST(cless_fend_file, empty_file) {
    std::filesystem::path path = root_path / "test-data/empty_file.c";

    File f(path);
    ASSERT_EQ(f.getPath(), path);
    ASSERT_EQ(f.getContents(), "");
    ASSERT_EQ(f.getNumLines(), 0);
}

TEST(cless_fend_file, empty_main) {
    std::filesystem::path path = root_path / "test-data/empty_main.c";

    File f(path);
    ASSERT_EQ(f.getPath(), path);
    ASSERT_EQ(f.getContents(), "int main(void) {}\n");
    ASSERT_EQ(f.getNumLines(), 1);
    ASSERT_EQ(f.getLine(0), "int main(void) {}");
}

TEST(cless_fend_file, return_only_main) {
    std::filesystem::path path = root_path / "test-data/return_only_main.c";

    File f(path);
    ASSERT_EQ(f.getPath(), path);
    ASSERT_EQ(f.getNumLines(), 3);
    ASSERT_EQ(f.getLine(0), "int main(void) {");
    ASSERT_EQ(f.getLine(1), "    return 0;");
    ASSERT_EQ(f.getLine(2), "}");
}
