#include <iostream>

#include "cli/parser.hpp"
#include "detector/star_detector.hpp"
#include "opencl/engine.hpp"
#include "scanner/directory_scanner.hpp"
#include "utils/result_writer.hpp"

int main(int argc, char* argv[]) {
    astra::CliOptions opts = astra::parse_args(argc, argv);
    auto files = astra::scan_directory(opts.directory);

    if (files.empty()) {
        std::cerr << "No JPEG files found in: " << opts.directory << "\n";
        return 1;
    }

    astra::OpenclEngine engine;
    astra::StarDetector detector(opts.threshold, opts.window_size);

    std::vector<astra::DetectionResult> results;
    for (const auto& f : files) {
        auto r = detector.detect(f);
        results.push_back({r.filename, r.star_count});
    }

    astra::write_results(results);
    return 0;
}
