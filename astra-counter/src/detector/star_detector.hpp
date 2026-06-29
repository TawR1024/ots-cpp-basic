#pragma once

#include <string>
#include <vector>

namespace astra {

struct StarPoint {
    int x = 0;
    int y = 0;
};

struct StarCountResult {
    std::string filename;
    int star_count = 0;
    std::vector<StarPoint> positions;
};

class StarDetector {
public:
    StarDetector(float threshold = 0.5f, int window_size = 5);

    StarCountResult detect(const std::string& filename) const;

private:
    float threshold_;
    int window_size_;
};

} // namespace astra
