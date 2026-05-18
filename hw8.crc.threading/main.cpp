#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes (std::vector<char>& data, uint32_t value)
{
    std::copy_n (reinterpret_cast<const char*> (&value), 4, data.end () - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack (const std::vector<char>& original, const std::string& injection)
{
    const uint32_t originalCrc32 = crc32 (original.data (), original.size ());

    std::vector<char> result (original.size () + injection.size () + 4);
    auto              it = std::copy (original.begin (), original.end (), result.begin ());
    std::copy (injection.begin (), injection.end (), it);

    /*
     * Внимание: код ниже крайне не оптимален.
     * В качестве доп. задания устраните избыточные вычисления
     */
    const size_t maxVal = std::numeric_limits<uint32_t>::max ();
    for (size_t i = 0; i < maxVal; ++i)
    {
        // Заменяем последние четыре байта на значение i
        replaceLastFourBytes (result, uint32_t (i));
        // Вычисляем CRC32 текущего вектора result
        auto currentCrc32 = crc32 (result.data (), result.size ());

        if (currentCrc32 == originalCrc32)
        {
            std::cout << "Success\n";
            return result;
        }
        // Отображаем прогресс
        if (i % 1000 == 0)
        {
            std::cout << "progress: " << static_cast<double> (i) / static_cast<double> (maxVal) << std::endl;
        }
    }
    throw std::logic_error ("Can't hack");
}

void worker (uint64_t start, uint64_t end, uint32_t targetCRC, uint32_t prefixCRC, std::atomic<bool>& stop,
             std::atomic<uint32_t>& found)
{
    std::cout << "starting thread: " << std::this_thread::get_id () << " start: " << start << " end: " << end
              << std::endl;
    for (auto i = start; i < end; i++)
    {
        if (stop.load ())
        {
            std::cout << "got stop signal" << std::endl;
            return;
        }

        // replaceLastFourBytes (result, static_cast<uint32_t> (i));
        char lastBytesp[4];
        std::copy_n(reinterpret_cast<const char*>(&i), 4, lastBytesp);
        auto currentCRC = crc32 (lastBytesp, 4, prefixCRC);
        if (currentCRC == targetCRC)
        {
            found.store (static_cast<uint32_t> (i));
            stop.store (true);
            std::cout << "thread id: " << std::this_thread::get_id () << " found target" << std::endl;
            return;
        }
    }

    std::cout << "thread id: " << std::this_thread::get_id () << "failed to found target" << std::endl;
}

std::vector<char> hack_threads (const std::vector<char>& original, const std::string& injection)
{
    const uint32_t targetCRC = crc32 (original.data (), original.size ());

    std::vector<char> result (original.size () + injection.size () + 4);
    auto it = std::copy (original.begin (), original.end (), result.begin ());
    std::copy (injection.begin (), injection.end (), it);

    // calculate crc for original vector and ijection
    uint32_t prefixCRC32 = ~crc32(result.data(), original.size() + injection.size());


    const unsigned int t           = std::thread::hardware_concurrency ()/2;
    const uint64_t     totalValues = static_cast<uint64_t> (std::numeric_limits<uint32_t>::max ()) + 1;
    const uint64_t     chunkSize   = totalValues / t;
    const uint64_t     remainder   = totalValues % t;

    std::atomic<bool>     stop{false};
    std::atomic<uint32_t> foundValue{0};

    std::vector<std::thread> threads;
    threads.reserve (t);

    uint64_t start = 0;
    for (unsigned int i = 0; i < t; ++i)
    {
        uint64_t end = start + chunkSize + (i < remainder ? 1 : 0);
        threads.emplace_back (worker, start, end, targetCRC, prefixCRC32, std::ref (stop), std::ref (foundValue));
        start = end;
    }

    for (auto& t : threads)
    {
        t.join ();
    }

    if (stop.load ())
    {
        replaceLastFourBytes (result, foundValue.load ());
        return result;
    }

    throw std::logic_error ("Can't hack");
}

int main (int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Call with two args: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    try
    {
        const std::vector<char> data = readFromFile (argv[1]);

        auto                    start   = std::chrono::steady_clock::now ();
        const std::vector<char> badData = hack_threads (data, "He-he-he");
        auto                    end     = std::chrono::steady_clock::now ();

        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count ();
        std::cout << "elapsed time: " << elapsed_ms << " ms\n";
        writeToFile (argv[2], badData);
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what () << '\n';
        return 2;
    }
    return 0;
}
