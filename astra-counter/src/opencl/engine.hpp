#pragma once

#include <string>

#ifdef HAVE_OPENCL
#include <CL/opencl.hpp>
#endif

namespace astra {

class OpenclEngine {
public:
    OpenclEngine();
    ~OpenclEngine() = default;

    bool is_available() const { return available_; }
    bool cv_opencl_available() const;
    std::string device_name() const;

private:
    bool available_ = false;
    std::string device_name_;

#ifdef HAVE_OPENCL
    cl::Platform platform_;
    cl::Device device_;
    cl::Context context_;
    cl::CommandQueue queue_;
#endif
};

} // namespace astra
