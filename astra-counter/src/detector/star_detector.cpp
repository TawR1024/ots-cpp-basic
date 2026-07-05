#include "detector/star_detector.hpp"

#include <chrono>
#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>

#include "loader/jpeg_loader.hpp"

namespace astra
{

StarDetector::StarDetector (float threshold, int window_size, bool use_gpu)
    : threshold_{threshold}, window_size_{window_size}, use_gpu_{use_gpu}
{
}

StarCountResult StarDetector::detect (const std::string& filename) const
{
    auto            t0 = std::chrono::steady_clock::now ();
    StarCountResult result;

    if (filename.empty ())
    {
        return result;
    }

    if (use_gpu_ && cv::ocl::haveOpenCL ())
    {
        result = detect_gpu (filename);
    }
    else
    {
        result = detect_cpu (filename);
    }

    auto t1           = std::chrono::steady_clock::now ();
    result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds> (t1 - t0).count ();
    return result;
}

StarCountResult StarDetector::detect_cpu (const std::string& filename) const
{
    StarCountResult result;
    result.filename   = filename;
    result.star_count = 0;

    cv::Mat gray = load_jpeg (filename);
    if (gray.empty ())
    {
        return result;
    }

    cv::Mat blurred;
    cv::GaussianBlur (gray, blurred, cv::Size{3, 3}, 0.5);

    cv::Mat dilated;
    cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size{window_size_, window_size_});
    cv::dilate (blurred, dilated, kernel);

    cv::Mat local_max;
    cv::compare (blurred, dilated, local_max, cv::CMP_EQ);

    cv::Mat threshold_mask;
    cv::threshold (blurred, threshold_mask, threshold_, 255.0, cv::THRESH_BINARY);
    threshold_mask.convertTo (threshold_mask, CV_8UC1);

    cv::Mat combined;
    cv::bitwise_and (local_max, threshold_mask, combined);

    result.star_count = cv::countNonZero (combined);

    for (int y = 0; y < combined.rows; ++y)
    {
        const auto* row = combined.ptr<uchar> (y);
        for (int x = 0; x < combined.cols; ++x)
        {
            if (row[x])
            {
                result.positions.push_back ({x, y});
            }
        }
    }

    return result;
}

StarCountResult StarDetector::detect_gpu (const std::string& filename) const
{
    StarCountResult result;
    result.filename   = filename;
    result.star_count = 0;

    cv::Mat gray_host = load_jpeg (filename);
    if (gray_host.empty ())
    {
        return result;
    }

    cv::UMat gray = gray_host.getUMat (cv::ACCESS_READ);

    cv::UMat blurred;
    cv::GaussianBlur (gray, blurred, cv::Size{3, 3}, 0.5);

    cv::UMat dilated;
    cv::Mat  kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size{window_size_, window_size_});
    cv::dilate (blurred, dilated, kernel);

    cv::UMat local_max;
    cv::compare (blurred, dilated, local_max, cv::CMP_EQ);

    cv::UMat threshold_mask;
    cv::threshold (blurred, threshold_mask, threshold_, 255.0, cv::THRESH_BINARY);
    threshold_mask.convertTo (threshold_mask, CV_8UC1);

    cv::UMat combined;
    cv::bitwise_and (local_max, threshold_mask, combined);

    result.star_count = cv::countNonZero (combined);

    cv::Mat combined_cpu;
    combined.copyTo (combined_cpu);

    for (int y = 0; y < combined_cpu.rows; ++y)
    {
        const auto* row = combined_cpu.ptr<uchar> (y);
        for (int x = 0; x < combined_cpu.cols; ++x)
        {
            if (row[x])
            {
                result.positions.push_back ({x, y});
            }
        }
    }

    return result;
}

}  // namespace astra
