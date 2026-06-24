#include <iostream>

#include "cli/parser.hpp"
#include "scanner/directory_scanner.hpp"

int main(int argc, char* argv[]) {
    try {
        auto opts = astra::parse_args(argc, argv);
        auto files = astra::scan_directory(opts.directory);

        if (files.empty()) {
            std::cerr << "No JPEG files found in: " << opts.directory << "\n";
            return 1;
        }

        for (const auto& f : files) {
            std::cout << f << "\n";
        }
    } catch (const astra::ConfigException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
