#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <atomic>

std::mutex threadMutex;
std::atomic<int> nextNumber;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

void showTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    std::cout << std::put_time(&now_tm, " %Y-%m-%d %H:%M:%S") << "\n";
}

void threadFunction(int threadId, int maxNumber)
{
    while (true)
    {
        int num = nextNumber.fetch_add(1);
        if (num > maxNumber)
            break;

        if (isPrime(num))
        {
            std::cout << "Thread " << threadId << " found prime: " << num << " || ";
            showTime();
        }
    }
}

bool readConfig(const std::string &filename, int &threadCount, int &range)
{
    std::ifstream config(filename);
    if (!config)
    {
        std::cerr << "Error opening config file.\n";
        return false;
    }

    std::string line;
    if (!std::getline(config, line))
    {
        std::cerr << "Error: Config file is empty.\n";
        return false;
    }

    std::istringstream iss(line);
    if (!(iss >> threadCount >> range) || !(iss.eof()))
    {
        std::cerr << "Error: Invalid input format. Ensure two integers are provided.\n";
        return false;
    }

    if (threadCount <= 0)
    {
        std::cerr << "Error: Thread count must be a positive integer.\n";
        return false;
    }

    if (range <= 1)
    {
        std::cerr << "Error: Range must be greater than 1.\n";
        return false;
    }

    return true;
}