#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <vector>

void showTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    std::cout << std::put_time(&now_tm, " %Y-%m-%d %H:%M:%S") << "\n";
}

bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n == 2)
    {
        return true;
    }
    if (n % 2 == 0)
    {
        return false;
    }

    for (int i = 3; i < n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

void threadFunction(int threadId, int range, int extra)
{
    int start = range * (threadId - 1);
    int end = range * threadId;

    if (threadId >= extra)
    {
        start += extra;
        end += extra;
    }
    else if (threadId < extra)
    {
        start += threadId;
        end += threadId;
    }

    for (int i = start; i < end; i++)
    {
        // if (isPrime(i))
        // {
        //     auto now = std::chrono::system_clock::now();
        //     std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        //     std::tm now_tm = *std::localtime(&now_time_t);
        //     std::cout << i << " is a prime number " << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "\n";
        // }
        std::cout << i << "\n";
    }
}

int main()
{
    int threadCount, range;
    std::vector<std::thread> threads;
    std::ifstream config("config.txt");

    if (!(config >> threadCount >> range))
    {
        std::cerr << "Error reading config file.\n";
        return 1;
    }

    std::cout << "Starting Execution at: ";
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

    std::cout << "Finished Execution at: ";
    showTime();

    system("pause");

    return 0;
}
