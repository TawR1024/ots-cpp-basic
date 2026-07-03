#include <gtest/gtest.h>
#include "detector/star_detector.hpp"
#include "opencl/engine.hpp"
#include "scanner/directory_scanner.hpp"
#include "utils/thread_pool.hpp"

#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class PerformanceTest : public ::testing::Test {
protected:
    fs::path tmp_dir;

    void SetUp() override {
        tmp_dir = fs::temp_directory_path() / "astra_perf";
        fs::remove_all(tmp_dir);
        fs::create_directories(tmp_dir);

        const int num_images = 20;
        for (int i = 0; i < num_images; ++i) {
            cv::Mat img(1000, 1000, CV_8UC1, cv::Scalar(0));
            for (int s = 0; s < 50; ++s) {
                int x = rand() % 900 + 50;
                int y = rand() % 900 + 50;
                cv::circle(img, cv::Point(x, y), 3, cv::Scalar(255), -1);
            }
            cv::imwrite((tmp_dir / ("img_" + std::to_string(i) + ".jpg")).string(), img);
        }
    }

    void TearDown() override {
        fs::remove_all(tmp_dir);
    }
};

TEST_F(PerformanceTest, ParallelFasterThanSequential) {
    auto files = astra::scan_directory(tmp_dir.string());
    ASSERT_EQ(files.size(), 20u);

    auto t1 = std::chrono::steady_clock::now();
    for (const auto& f : files) {
        astra::StarDetector detector{0.1f, 5};
        detector.detect(f);
    }
    auto t_seq = std::chrono::steady_clock::now() - t1;

    astra::ThreadPool pool;
    t1 = std::chrono::steady_clock::now();
    std::vector<std::future<astra::StarCountResult>> futures;
    for (const auto& f : files) {
        futures.push_back(pool.submit([f]() {
            astra::StarDetector detector{0.1f, 5};
            return detector.detect(f);
        }));
    }
    for (auto& fut : futures) {
        fut.get();
    }
    auto t_par = std::chrono::steady_clock::now() - t1;

    auto ms_seq = std::chrono::duration_cast<std::chrono::milliseconds>(t_seq).count();
    auto ms_par = std::chrono::duration_cast<std::chrono::milliseconds>(t_par).count();
    std::cout << "  Sequential: " << ms_seq << "ms\n";
    std::cout << "  Parallel:   " << ms_par << "ms\n";
    std::cout << "  Speedup:    " << static_cast<double>(ms_seq) / ms_par << "x\n";

    EXPECT_LT(t_par, t_seq * 0.85);
}

TEST_F(PerformanceTest, GpuVsCpuBenchmark) {
    astra::OpenclEngine ocl;
    if (!ocl.is_available() || !cv::ocl::haveOpenCL()) {
        GTEST_SKIP() << "OpenCL GPU not available, skipping GPU benchmark";
    }

    auto files = astra::scan_directory(tmp_dir.string());
    ASSERT_EQ(files.size(), 20u);

    auto t1 = std::chrono::steady_clock::now();
    for (const auto& f : files) {
        astra::StarDetector detector{0.1f, 5, false};
        detector.detect(f);
    }
    auto t_cpu = std::chrono::steady_clock::now() - t1;

    t1 = std::chrono::steady_clock::now();
    for (const auto& f : files) {
        astra::StarDetector detector{0.1f, 5, true};
        detector.detect(f);
    }
    auto t_gpu = std::chrono::steady_clock::now() - t1;

    auto ms_cpu = std::chrono::duration_cast<std::chrono::milliseconds>(t_cpu).count();
    auto ms_gpu = std::chrono::duration_cast<std::chrono::milliseconds>(t_gpu).count();
    std::cout << "  CPU:        " << ms_cpu << "ms\n";
    std::cout << "  GPU:        " << ms_gpu << "ms\n";
    if (ms_gpu > 0) {
        std::cout << "  Speedup:    " << static_cast<double>(ms_cpu) / ms_gpu << "x\n";
    }
}
