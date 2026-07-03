#pragma once

#include <opencv2/core.hpp>
#include <string>

namespace astra {

cv::Mat load_jpeg(const std::string& filepath);

} // namespace astra
