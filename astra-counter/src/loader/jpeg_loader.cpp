#include "loader/jpeg_loader.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <stdexcept>

namespace astra {

ImageData load_jpeg(const std::string& filepath) {
    cv::Mat mat = cv::imread(filepath, cv::IMREAD_GRAYSCALE);
    if (mat.empty()) {
        throw std::runtime_error("Failed to load image: " + filepath);
    }

    cv::Mat float_mat;
    mat.convertTo(float_mat, CV_32F, 1.0 / 255.0);

    ImageData data;
    data.width = float_mat.cols;
    data.height = float_mat.rows;
    data.pixels.resize(static_cast<size_t>(data.width) * data.height);

    for (int y = 0; y < data.height; ++y) {
        const float* row = float_mat.ptr<float>(y);
        std::copy(row, row + data.width,
                  data.pixels.begin() + static_cast<size_t>(y) * data.width);
    }

    return data;
}

} // namespace astra
