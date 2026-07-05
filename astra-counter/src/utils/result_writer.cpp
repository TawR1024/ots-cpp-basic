#include "utils/result_writer.hpp"
#include "detector/star_detector.hpp"

#include <iomanip>
#include <iostream>

namespace astra {

void write_results(const std::vector<DetectionResult>& results) {
    for (const auto& r : results) {
        std::cout << r.filename << ": " << r.star_count << " stars\n";
    }
}

void write_results(const std::vector<StarCountResult>& results) {
    for (const auto& r : results) {
        std::cout << std::setw(40) << std::left << r.filename
                  << " | stars: " << r.star_count << "\n";
    }
}

} // namespace astra
