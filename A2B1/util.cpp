#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>

std::mutex threadMutex;
std::vector<std::string> primeResults;

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

void showTime(std::string &formattedTime)
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream timeStream;
    timeStream << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S")
               << "." << std::setw(3) << std::setfill('0') << milliseconds.count();

    formattedTime = timeStream.str(); // Set the time in the passed reference
}

void threadFunction(int threadId, int range, int extra)
{
    int start = range * (threadId - 1) + 1;
    int end = range * threadId;

    if (threadId <= extra)
    {
        start += threadId - 1;
        end += threadId;
    }
    else if (threadId > extra)
    {
        start += extra;
        end += extra;
    }

    for (int i = start; i < end + 1; i++)
    {
        if (isPrime(i))
        {
            std::string currentTime;
            showTime(currentTime);

            std::lock_guard<std::mutex> lock(threadMutex);
            primeResults.push_back("Thread " + std::to_string(threadId) + " found prime: " + std::to_string(i) + " || " + currentTime + "\n");
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