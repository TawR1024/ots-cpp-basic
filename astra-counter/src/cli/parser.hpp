#pragma once

#include <string>
#include <vector>

namespace astra {

struct CliOptions {
    std::string directory;
    float threshold = 0.5f;
    int window_size = 5;
};

CliOptions parse_args(int argc, char* argv[]);

} // namespace astra
