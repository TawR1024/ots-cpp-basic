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
    long elapsed_ms = 0;
};

class StarDetector {
public:
    StarDetector(float threshold = 0.5f, int window_size = 5,
                 bool use_gpu = false);

    StarCountResult detect(const std::string& filename) const;

private:
    StarCountResult detect_cpu(const std::string& filename) const;
    StarCountResult detect_gpu(const std::string& filename) const;

    float threshold_;
    int window_size_;
    bool use_gpu_;
};

} // namespace astra
