#include "opencl/engine.hpp"

#include <opencv2/core/ocl.hpp>

namespace astra
{

OpenclEngine::OpenclEngine ()
{
#ifdef HAVE_OPENCL
    std::vector<cl::Platform> platforms;
    cl_int                    err = cl::Platform::get (&platforms);
    if (err != CL_SUCCESS || platforms.empty ())
    {
        available_ = false;
        return;
    }

    platform_ = platforms[0];
    std::vector<cl::Device> devices;
    err = platform_.getDevices (CL_DEVICE_TYPE_GPU, &devices);
    if (err != CL_SUCCESS || devices.empty ())
    {
        err = platform_.getDevices (CL_DEVICE_TYPE_ALL, &devices);
        if (err != CL_SUCCESS || devices.empty ())
        {
            available_ = false;
            return;
        }
    }

    device_      = devices[0];
    context_     = cl::Context (device_);
    queue_       = cl::CommandQueue (context_, device_);
    available_   = true;
    device_name_ = device_.getInfo<CL_DEVICE_NAME> ();
#else
    available_ = false;
#endif
}

bool OpenclEngine::cv_opencl_available () const { return cv::ocl::haveOpenCL () && cv::ocl::useOpenCL (); }

std::string OpenclEngine::device_name () const
{
    if (!available_)
        return "none (CPU mode)";
    return device_name_;
}

}  // namespace astra
