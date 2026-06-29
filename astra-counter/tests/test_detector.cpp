#include <gtest/gtest.h>
#include "detector/star_detector.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class DetectorTest : public ::testing::Test {
protected:
    fs::path tmp_dir;

    void SetUp() override {
        tmp_dir = fs::temp_directory_path() / "astra_detector_test";
        fs::remove_all(tmp_dir);
        fs::create_directories(tmp_dir);
    }

    void TearDown() override {
        fs::remove_all(tmp_dir);
    }

    std::string make_image_with_stars(int width, int height,
                                      const std::vector<cv::Point>& centers,
                                      int star_radius = 2) {
        cv::Mat img(height, width, CV_8UC1, cv::Scalar(0));
        for (const auto& c : centers) {
            cv::circle(img, c, star_radius, cv::Scalar(255), -1);
        }
        auto path = tmp_dir / "stars.jpg";
        cv::imwrite(path.string(), img);
        return path.string();
    }
};

TEST_F(DetectorTest, SingleStar) {
    auto path = make_image_with_stars(100, 100, {{50, 50}});
    astra::StarDetector detector(0.1f, 5);
    auto result = detector.detect(path);
    EXPECT_EQ(result.star_count, 1);
}

TEST_F(DetectorTest, MultipleStars) {
    auto path = make_image_with_stars(200, 200,
        {{30, 30}, {80, 80}, {150, 150}});
    astra::StarDetector detector(0.1f, 5);
    auto result = detector.detect(path);
    EXPECT_EQ(result.star_count, 3);
}

TEST_F(DetectorTest, NoStarsOnBlackImage) {
    cv::Mat img(50, 50, CV_8UC1, cv::Scalar(0));
    auto path = (tmp_dir / "black.jpg").string();
    cv::imwrite(path, img);
    astra::StarDetector detector(0.1f, 5);
    auto result = detector.detect(path);
    EXPECT_EQ(result.star_count, 0);
}

TEST_F(DetectorTest, ThresholdFiltersDimStars) {
    cv::Mat img(100, 100, CV_8UC1, cv::Scalar(0));
    cv::circle(img, cv::Point(30, 30), 3, cv::Scalar(255), -1);
    cv::circle(img, cv::Point(70, 70), 3, cv::Scalar(100), -1);
    auto path = (tmp_dir / "mixed.jpg").string();
    cv::imwrite(path, img);

    astra::StarDetector detector(0.8f, 5);
    auto result = detector.detect(path);
    EXPECT_EQ(result.star_count, 1);
}

TEST_F(DetectorTest, EmptyPathReturnsZero) {
    astra::StarDetector detector(0.5f, 5);
    auto result = detector.detect("");
    EXPECT_EQ(result.star_count, 0);
}
