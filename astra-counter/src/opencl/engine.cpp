#include "opencl/engine.hpp"

namespace astra {

OpenclEngine::OpenclEngine() {
    std::vector<cl::Platform> platforms;
    cl_int err = cl::Platform::get(&platforms);
    if (err != CL_SUCCESS || platforms.empty()) {
        available_ = false;
        return;
    }

    platform_ = platforms[0];
    std::vector<cl::Device> devices;
    err = platform_.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    if (err != CL_SUCCESS || devices.empty()) {
        available_ = false;
        return;
    }

    device_ = devices[0];
    context_ = cl::Context(device_);
    queue_ = cl::CommandQueue(context_, device_);
    available_ = true;
}

std::string OpenclEngine::device_name() const {
    if (!available_) return "none";
    return device_.getInfo<CL_DEVICE_NAME>();
}

} // namespace astra
