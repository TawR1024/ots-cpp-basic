#pragma once

#include <CL/opencl.hpp>
#include <string>

namespace astra {

class OpenclEngine {
public:
    OpenclEngine();
    ~OpenclEngine() = default;

    bool is_available() const { return available_; }
    std::string device_name() const;

private:
    bool available_ = false;
    cl::Platform platform_;
    cl::Device device_;
    cl::Context context_;
    cl::CommandQueue queue_;
};

} // namespace astra
