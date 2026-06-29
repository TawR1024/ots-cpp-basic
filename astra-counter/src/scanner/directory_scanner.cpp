#include "scanner/directory_scanner.hpp"

#include <algorithm>
#include <filesystem>
#include <vector>

namespace astra {

static bool is_jpeg_extension(const std::filesystem::path& p) {
    std::string ext = p.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return ext == ".jpg" || ext == ".jpeg";
}

std::vector<std::string> scan_directory(const std::string& path) {
    std::vector<std::string> files;

    std::filesystem::path dir(path);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        return files;
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file() && is_jpeg_extension(entry.path())) {
            files.push_back(entry.path().string());
        }
    }

    std::sort(files.begin(), files.end());
    return files;
}

} // namespace astra
