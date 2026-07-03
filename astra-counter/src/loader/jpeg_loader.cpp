#include "loader/jpeg_loader.hpp"

#include <opencv2/imgcodecs.hpp>
#include <stdexcept>

namespace astra {

cv::Mat load_jpeg(const std::string& filepath) {
    cv::Mat mat = cv::imread(filepath, cv::IMREAD_GRAYSCALE);
    if (mat.empty()) {
        throw std::runtime_error("Failed to load image: " + filepath);
    }

    cv::Mat float_mat;
    mat.convertTo(float_mat, CV_32F, 1.0 / 255.0);
    return float_mat;
}

} // namespace astra
