#include <gtest/gtest.h>
#include "cli/parser.hpp"

#include <filesystem>

namespace fs = std::filesystem;

TEST(CliParser, DefaultThreshold) {
    astra::CliOptions opts;
    EXPECT_FLOAT_EQ(opts.threshold, 0.5f);
}

TEST(CliParser, DefaultWindowSize) {
    astra::CliOptions opts;
    EXPECT_EQ(opts.window_size, 5);
}

TEST(CliParser, ParseArgsWithDir) {
    auto dir = fs::current_path().string();
    char arg0[] = "astra-counter";
    char arg1[] = "--dir";
    std::vector<char> dir_buf(dir.begin(), dir.end());
    dir_buf.push_back('\0');
    char* argv[] = {arg0, arg1, dir_buf.data()};
    auto opts = astra::parse_args(3, argv);
    EXPECT_EQ(opts.directory, dir);
    EXPECT_FLOAT_EQ(opts.threshold, 0.5f);
    EXPECT_EQ(opts.window_size, 5);
}

TEST(CliParser, ParseArgsCustomThreshold) {
    auto dir = fs::current_path().string();
    char arg0[] = "astra-counter";
    char arg1[] = "--dir";
    std::vector<char> dir_buf(dir.begin(), dir.end());
    dir_buf.push_back('\0');
    char arg2[] = "--threshold";
    char arg3[] = "0.8";
    char* argv[] = {arg0, arg1, dir_buf.data(), arg2, arg3};
    auto opts = astra::parse_args(5, argv);
    EXPECT_FLOAT_EQ(opts.threshold, 0.8f);
}

TEST(CliParser, InvalidThresholdNegative) {
    auto dir = fs::current_path().string();
    char arg0[] = "astra-counter";
    char arg1[] = "--dir";
    std::vector<char> dir_buf(dir.begin(), dir.end());
    dir_buf.push_back('\0');
    char arg2[] = "--threshold";
    char arg3[] = "-1.0";
    char* argv[] = {arg0, arg1, dir_buf.data(), arg2, arg3};
    EXPECT_THROW(astra::parse_args(5, argv), astra::ConfigException);
}

TEST(CliParser, InvalidThresholdOverOne) {
    auto dir = fs::current_path().string();
    char arg0[] = "astra-counter";
    char arg1[] = "--dir";
    std::vector<char> dir_buf(dir.begin(), dir.end());
    dir_buf.push_back('\0');
    char arg2[] = "--threshold";
    char arg3[] = "1.5";
    char* argv[] = {arg0, arg1, dir_buf.data(), arg2, arg3};
    EXPECT_THROW(astra::parse_args(5, argv), astra::ConfigException);
}

TEST(CliParser, InvalidWindowEven) {
    auto dir = fs::current_path().string();
    char arg0[] = "astra-counter";
    char arg1[] = "--dir";
    std::vector<char> dir_buf(dir.begin(), dir.end());
    dir_buf.push_back('\0');
    char arg2[] = "--window";
    char arg3[] = "4";
    char* argv[] = {arg0, arg1, dir_buf.data(), arg2, arg3};
    EXPECT_THROW(astra::parse_args(5, argv), astra::ConfigException);
}

TEST(CliParser, MissingDirectoryArg) {
    char arg0[] = "astra-counter";
    char* argv[] = {arg0};
    EXPECT_THROW(astra::parse_args(1, argv), astra::ConfigException);
}
