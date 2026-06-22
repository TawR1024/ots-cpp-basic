#include "utils/result_writer.hpp"

#include <iostream>

namespace astra {

void write_results(const std::vector<DetectionResult>& results) {
    for (const auto& r : results) {
        std::cout << r.filename << ": " << r.star_count << " stars\n";
    }
}

} // namespace astra
