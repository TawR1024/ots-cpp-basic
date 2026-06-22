#include <gtest/gtest.h>
#include "scanner/directory_scanner.hpp"

TEST(DirectoryScanner, NonexistentDirReturnsEmpty) {
    auto files = astra::scan_directory("/nonexistent_path_12345");
    EXPECT_TRUE(files.empty());
}
