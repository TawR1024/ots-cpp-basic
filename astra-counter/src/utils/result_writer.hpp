#pragma once

#include <string>
#include <vector>

namespace astra {

struct DetectionResult {
    std::string filename;
    int star_count = 0;
};

struct StarCountResult;

void write_results(const std::vector<DetectionResult>& results);
void write_results(const std::vector<StarCountResult>& results);

} // namespace astra
