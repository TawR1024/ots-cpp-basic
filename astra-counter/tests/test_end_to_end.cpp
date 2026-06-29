#include <gtest/gtest.h>
#include "detector/star_detector.hpp"
#include "scanner/directory_scanner.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

TEST(EndToEnd, DetectsKnownStarCount) {
    fs::path tmp = fs::temp_directory_path() / "astra_e2e";
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    cv::Mat img(200, 200, CV_8UC1, cv::Scalar(0));
    std::vector<cv::Point> stars = {
        {30, 30}, {80, 80}, {130, 130}, {160, 40}, {40, 160}
    };
    for (const auto& s : stars) {
        cv::circle(img, s, 2, cv::Scalar(255), -1);
    }
    cv::imwrite((tmp / "stars.jpg").string(), img);

    auto files = astra::scan_directory(tmp.string());
    ASSERT_EQ(files.size(), 1u);

    astra::StarDetector detector(0.1f, 5);
    auto result = detector.detect(files[0]);
    EXPECT_EQ(result.star_count, 5);

    fs::remove_all(tmp);
}
