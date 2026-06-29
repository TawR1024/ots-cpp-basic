#include "detector/star_detector.hpp"
#include "loader/jpeg_loader.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace astra {

StarDetector::StarDetector(float threshold, int window_size)
    : threshold_{threshold}, window_size_{window_size} {}

StarCountResult StarDetector::detect(const std::string& filename) const {
    StarCountResult result;
    result.filename = filename;
    result.star_count = 0;

    if (filename.empty()) {
        return result;
    }

    ImageData data = load_jpeg(filename);
    if (data.width == 0 || data.height == 0) {
        return result;
    }

    cv::Mat gray(data.height, data.width, CV_32FC1, data.pixels.data());

    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size{3, 3}, 0.5);

    cv::Mat dilated;
    cv::Mat kernel = cv::getStructuringElement(
        cv::MORPH_RECT, cv::Size{window_size_, window_size_});
    cv::dilate(blurred, dilated, kernel);

    cv::Mat local_max;
    cv::compare(blurred, dilated, local_max, cv::CMP_EQ);

    cv::Mat threshold_mask;
    cv::threshold(blurred, threshold_mask, threshold_, 255.0, cv::THRESH_BINARY);
    threshold_mask.convertTo(threshold_mask, CV_8UC1);

    cv::Mat combined;
    cv::bitwise_and(local_max, threshold_mask, combined);

    result.star_count = cv::countNonZero(combined);

    for (int y = 0; y < combined.rows; ++y) {
        const auto* row = combined.ptr<uchar>(y);
        for (int x = 0; x < combined.cols; ++x) {
            if (row[x]) {
                result.positions.push_back({x, y});
            }
        }
    }

    return result;
}

} // namespace astra
