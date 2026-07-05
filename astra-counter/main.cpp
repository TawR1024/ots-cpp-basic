#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>

#include "cli/parser.hpp"
#include "detector/star_detector.hpp"
#include "opencl/engine.hpp"
#include "scanner/directory_scanner.hpp"
#include "utils/thread_pool.hpp"

#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace fs = std::filesystem;

static void save_annotated(const astra::StarCountResult& result,
                            const std::string& output_dir) {
    cv::Mat img = cv::imread(result.filename, cv::IMREAD_COLOR);
    if (img.empty()) return;

    for (const auto& p : result.positions) {
        cv::circle(img, cv::Point{p.x, p.y}, 4, cv::Scalar{0, 0, 255}, 1);
    }

    fs::path src(result.filename);
    fs::path dst = fs::path(output_dir) / src.filename();
    cv::imwrite(dst.string(), img);
}

static bool resolve_use_gpu(astra::Backend backend) {
    astra::OpenclEngine ocl;

    if (backend == astra::Backend::Cpu) {
        std::cout << "Backend: CPU (forced)\n";
        return false;
    }

    if (backend == astra::Backend::Gpu) {
        if (ocl.is_available() && ocl.cv_opencl_available()) {
            std::cout << "Backend: GPU - " << ocl.device_name() << " (forced)\n";
            return true;
        }
        std::cout << "Backend: CPU (GPU requested but not available)\n";
        return false;
    }

    if (ocl.is_available() && ocl.cv_opencl_available()) {
        std::cout << "Backend: GPU - " << ocl.device_name() << " (auto-detected)\n";
        return true;
    }

    std::cout << "Backend: CPU (no GPU found)\n";
    return false;
}

int main(int argc, char* argv[]) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

    try {
        auto opts = astra::parse_args(argc, argv);
        auto files = astra::scan_directory(opts.directory);

        if (files.empty()) {
            std::cerr << "No JPEG files found in: " << opts.directory << "\n";
            return 1;
        }

        if (!opts.output_annotated.empty()) {
            fs::create_directories(opts.output_annotated);
        }

        bool use_gpu = resolve_use_gpu(opts.backend);

        astra::ThreadPool pool;
        std::vector<std::future<astra::StarCountResult>> futures;
        futures.reserve(files.size());

        for (const auto& f : files) {
            futures.push_back(pool.submit([f, &opts, use_gpu]() {
                astra::StarDetector detector{opts.threshold, opts.window_size, use_gpu};
                return detector.detect(f);
            }));
        }

        std::cout << "Processing " << files.size() << " image(s)...\n";
        auto wall_start = std::chrono::steady_clock::now();
        long sum_ms = 0;
        int processed = 0;
        for (auto& fut : futures) {
            try {
                auto result = fut.get();
                std::cout << std::setw(40) << std::left << result.filename
                          << " | stars: " << result.star_count << "\n";

                sum_ms += result.elapsed_ms;
                ++processed;

                if (!opts.output_annotated.empty()) {
                    save_annotated(result, opts.output_annotated);
                }
            } catch (const std::exception& e) {
                std::cerr << "Failed to process image | error: " << e.what() << "\n";
            }
        }
        auto wall_end = std::chrono::steady_clock::now();

        auto wall_ms = std::chrono::duration_cast<std::chrono::milliseconds>(wall_end - wall_start).count();
        long avg_ms = processed > 0 ? sum_ms / processed : 0;

        std::cout << "\n--- Summary ---\n";
        std::cout << "Total:   " << wall_ms << "ms\n";
        std::cout << "Average: " << avg_ms << "ms\n";

        if (!opts.output_annotated.empty()) {
            std::cout << "\nAnnotated images saved to: " << opts.output_annotated << "\n";
        }
    } catch (const astra::ConfigException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
