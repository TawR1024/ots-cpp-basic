#include <filesystem>
#include <iomanip>
#include <iostream>

#include "cli/parser.hpp"
#include "detector/star_detector.hpp"
#include "scanner/directory_scanner.hpp"

#include <opencv2/core.hpp>
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

        astra::StarDetector detector{opts.threshold, opts.window_size};

        std::cout << "Processing " << files.size() << " image(s)...\n";
        for (const auto& f : files) {
            auto result = detector.detect(f);
            std::cout << std::setw(40) << std::left << result.filename
                      << " | stars: " << result.star_count << "\n";

            if (!opts.output_annotated.empty()) {
                save_annotated(result, opts.output_annotated);
            }
        }

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
