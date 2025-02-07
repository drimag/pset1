#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <ctime>

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

    // Convert the time point to a time_t, which represents the time in seconds since the epoch
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm structure for local time
    std::tm now_tm = *std::localtime(&now_time_t);

    std::cout << x << " " << y << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "\n";

    return 0;
}
