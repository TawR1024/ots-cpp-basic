// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

void worker(std::queue<std::string> &files, std::mutex& queue_mtx, Counter& common_dict, std::mutex& dict_mtx){
    while (true)
    {
        std::string file_path;
        {
            std::lock_guard<std::mutex> lock(queue_mtx);
            if (files.empty()) break;
            file_path = std::move(files.front());
            files.pop();
        }
        
        Counter file_dict;
        std::fstream input (file_path);
        if (!input.is_open()) {
            std::cerr << "Failed to open file " << file_path << '\n';
            continue;
        }
        count_words(input, file_dict);

        // update commont dictionary;
        {
            std::lock_guard<std::mutex> lock(dict_mtx);
            for(auto &[key, value]: file_dict){
                common_dict[key]+=value;
            }
        }
        
    }
        
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    // create files quue;
    std::queue<std::string> files;
    for (auto i = 1; i < argc; ++i){
        files.emplace(argv[i]);
    }
    
    Counter freq_dict;
    std::mutex files_mtx;
    std::mutex dict_mtx;

    unsigned int thread_count = std::thread::hardware_concurrency();
    if (argc < thread_count) {
        thread_count = std::min(thread_count, static_cast<unsigned int>(argc-1));
    }

    std::vector<std::thread> workers;
    for (auto t=0; t < thread_count; t ++ ) {
        workers.emplace_back(worker, std::ref(files), std::ref(files_mtx), std::ref(freq_dict), std::ref(dict_mtx));
    }

    auto start = std::chrono::high_resolution_clock::now();

    for(auto &w: workers){
        w.join();
    }
    

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}

