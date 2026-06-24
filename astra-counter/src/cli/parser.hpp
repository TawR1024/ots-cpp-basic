#pragma once

#include <stdexcept>
#include <string>

namespace astra {

struct CliOptions {
    std::string directory;
    float threshold = 0.5f;
    int window_size = 5;
};

class ConfigException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

CliOptions parse_args(int argc, char* argv[]);

} // namespace astra
