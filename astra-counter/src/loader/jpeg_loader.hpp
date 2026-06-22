#pragma once

#include <opencv2/core.hpp>
#include <string>
#include <vector>

namespace astra {

struct ImageData {
    int width = 0;
    int height = 0;
    std::vector<float> pixels;
};

ImageData load_jpeg(const std::string& filepath);

} // namespace astra
