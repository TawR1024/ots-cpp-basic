#include <gtest/gtest.h>
#include "scanner/directory_scanner.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class ScannerTest : public ::testing::Test {
protected:
    fs::path tmp_dir;

    void SetUp() override {
        tmp_dir = fs::temp_directory_path() / "astra_scanner_test";
        fs::remove_all(tmp_dir);
        fs::create_directories(tmp_dir);
    }

    void TearDown() override {
        fs::remove_all(tmp_dir);
    }

    void touch(const fs::path& p) {
        std::ofstream(p).close();
    }
};

TEST_F(ScannerTest, EmptyDirReturnsEmpty) {
    auto files = astra::scan_directory(tmp_dir.string());
    EXPECT_TRUE(files.empty());
}

TEST_F(ScannerTest, DirWithJpegs) {
    touch(tmp_dir / "a.jpg");
    touch(tmp_dir / "b.jpeg");
    touch(tmp_dir / "c.png");
    touch(tmp_dir / "d.txt");

    auto files = astra::scan_directory(tmp_dir.string());
    ASSERT_EQ(files.size(), 2u);
    EXPECT_NE(files[0].find("a.jpg"), std::string::npos);
    EXPECT_NE(files[1].find("b.jpeg"), std::string::npos);
}

TEST_F(ScannerTest, RecursiveScanning) {
    auto subdir = tmp_dir / "subdir";
    fs::create_directories(subdir);
    touch(tmp_dir / "top.jpg");
    touch(subdir / "nested.jpg");

    auto files = astra::scan_directory(tmp_dir.string());
    ASSERT_EQ(files.size(), 2u);
}

TEST_F(ScannerTest, NonexistentDirReturnsEmpty) {
    auto files = astra::scan_directory("/nonexistent_path_12345");
    EXPECT_TRUE(files.empty());
}

TEST_F(ScannerTest, CaseInsensitiveExtensions) {
    touch(tmp_dir / "upper.JPG");
    touch(tmp_dir / "mixed.Jpeg");

    auto files = astra::scan_directory(tmp_dir.string());
    EXPECT_EQ(files.size(), 2u);
}

TEST_F(ScannerTest, SortedOutput) {
    touch(tmp_dir / "z.jpg");
    touch(tmp_dir / "a.jpg");
    touch(tmp_dir / "m.jpg");

    auto files = astra::scan_directory(tmp_dir.string());
    ASSERT_EQ(files.size(), 3u);
    EXPECT_TRUE(std::is_sorted(files.begin(), files.end()));
}
