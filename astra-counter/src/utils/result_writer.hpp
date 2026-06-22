#pragma once

#include <string>
#include <vector>

namespace astra {

struct DetectionResult {
    std::string filename;
    int star_count = 0;
};

void write_results(const std::vector<DetectionResult>& results);

} // namespace astra
