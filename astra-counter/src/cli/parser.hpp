#pragma once

#include <stdexcept>
#include <string>

namespace astra {

enum class Backend { Auto, Cpu, Gpu };

struct CliOptions {
    std::string directory;
    std::string output_annotated;
    float threshold = 0.5f;
    int window_size = 5;
    Backend backend = Backend::Auto;
};

class ConfigException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

CliOptions parse_args(int argc, char* argv[]);

} // namespace astra
