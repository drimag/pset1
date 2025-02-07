#include "util.h"
#include <thread>

int main()
{
    int threadCount, range;
    std::vector<std::thread> threads;

    if (!readConfig("config.txt", threadCount, range))
    {
        system("pause");
        return 1;
    }

    std::cout << "Started Execution on: ";
    showTime();

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

    std::cout << "Finished Execution on: ";
    showTime();

    system("pause");

    return 0;
}
