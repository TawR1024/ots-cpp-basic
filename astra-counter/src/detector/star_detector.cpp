#include "detector/star_detector.hpp"

namespace astra {

StarDetector::StarDetector(float threshold, int window_size)
    : threshold_(threshold), window_size_(window_size) {}

StarCountResult StarDetector::detect(const std::string& filename) const {
    StarCountResult result;
    result.filename = filename;
    result.star_count = 0;
    return result;
}

} // namespace astra
