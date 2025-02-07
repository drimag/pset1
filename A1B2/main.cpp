#include "util.h"
#include <thread>

int main()
{
    int threadCount, max;
    std::vector<std::thread> threads;

    if (!readConfig("config.txt", threadCount, max))
    {
        system("pause");
        return 1;
    }

    std::cout << "Started Execution on: ";
    showTime();

    if (max < threadCount)
        threadCount = max;

    for (int i = 0; i < threadCount; ++i)
    {
        threads.emplace_back(threadFunction, i + 1, max);
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
