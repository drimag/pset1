#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <ctime>

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

int main()
{
    int x, y;
    std::ifstream config("config.txt");

    if (!(config >> x >> y))
    {
        std::cerr << "Error reading config file.\n";
        return 1;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    std::cout << x << " " << y << std::put_time(&now_tm, " %Y-%m-%d %H:%M:%S") << "\n";

    if (isPrime(x))
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time_t);

        // TODO: include thread no.
        std::cout << x << " is a prime number " << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "\n";
    }

    system("pause");

    return 0;
}
