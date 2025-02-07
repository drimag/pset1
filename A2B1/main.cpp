#include "util.h"
#include <thread>

int main()
{
    int threadCount, range;
    std::vector<std::thread> threads;

    if (!readConfig("config.txt", threadCount, range))
    {
        return 1;
    }

    std::string currentTime;
    showTime(currentTime);
    std::cout << "Started Execution on: " << currentTime << "\n";

    if (range < threadCount)
        threadCount = range;

    int rangePerThread = range / threadCount;
    int extra = range % threadCount;

    for (int i = 0; i < threadCount; ++i)
    {
        threads.emplace_back(threadFunction, i + 1, rangePerThread, extra);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    for (const auto &result : primeResults)
    {
        std::cout << result;
    }

    showTime(currentTime);
    std::cout << "Finished Execution on: " << currentTime << "\n";

    system("pause");

    return 0;
}
