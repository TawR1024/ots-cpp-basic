#include "cli/parser.hpp"

#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>

namespace astra {

CliOptions parse_args(int argc, char* argv[]) {
    CliOptions opts;

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "show help message")
        ("dir,d", boost::program_options::value<std::string>(&opts.directory)->required(),
         "directory containing JPEG images")
        ("threshold,t", boost::program_options::value<float>(&opts.threshold)->default_value(0.5f),
         "brightness threshold [0.0, 1.0]")
        ("window,w", boost::program_options::value<int>(&opts.window_size)->default_value(5),
         "local maxima window size (odd, >= 3)")
        ("output-annotated,o", boost::program_options::value<std::string>(&opts.output_annotated),
         "save annotated images to this directory");

    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    } catch (const boost::program_options::error& e) {
        throw ConfigException(e.what());
    }

    if (vm.count("help")) {
        std::cout << "Usage: astra-counter [options]\n\n" << desc << "\n";
        std::exit(0);
    }

    try {   
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        throw ConfigException(e.what());
    }

    if (opts.threshold < 0.0f || opts.threshold > 1.0f) {
        throw ConfigException("threshold must be in [0.0, 1.0]");
    }
    if (opts.window_size < 3 || opts.window_size % 2 == 0) {
        throw ConfigException("window size must be odd and >= 3");
    }
    if (!std::filesystem::exists(opts.directory)) {
        throw ConfigException("directory does not exist: " + opts.directory);
    }
    if (!std::filesystem::is_directory(opts.directory)) {
        throw ConfigException("path is not a directory: " + opts.directory);
    }

    return opts;
}

} // namespace astra
