#include <gtest/gtest.h>
#include "loader/jpeg_loader.hpp"

#include <filesystem>
#include <numeric>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace fs = std::filesystem;

class LoaderTest : public ::testing::Test {
protected:
    fs::path tmp_dir;

    void SetUp() override {
        tmp_dir = fs::temp_directory_path() / "astra_loader_test";
        fs::remove_all(tmp_dir);
        fs::create_directories(tmp_dir);
    }

    void TearDown() override {
        fs::remove_all(tmp_dir);
    }
};

TEST_F(LoaderTest, SyntheticGrayscaleLoad) {
    cv::Mat img(10, 20, CV_8UC1, cv::Scalar(255));
    auto path = (tmp_dir / "gray.jpg").string();
    cv::imwrite(path, img);

    auto data = astra::load_jpeg(path);
    EXPECT_EQ(data.width, 20);
    EXPECT_EQ(data.height, 10);
    EXPECT_EQ(data.pixels.size(), static_cast<size_t>(200));
    for (float p : data.pixels) {
        EXPECT_NEAR(p, 1.0f, 0.02f);
    }
}

TEST_F(LoaderTest, NonexistentFileThrows) {
    EXPECT_THROW(astra::load_jpeg("/nonexistent/path/file.jpg"), std::runtime_error);
}

TEST_F(LoaderTest, MixedColorImageBecomesGrayscale) {
    cv::Mat img(8, 16, CV_8UC3, cv::Scalar(100, 150, 200));
    auto path = (tmp_dir / "color.jpg").string();
    cv::imwrite(path, img);

    auto data = astra::load_jpeg(path);
    EXPECT_EQ(data.width, 16);
    EXPECT_EQ(data.height, 8);
    EXPECT_EQ(data.pixels.size(), static_cast<size_t>(16 * 8));
}
