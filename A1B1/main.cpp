#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
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

    std::cout << x << " " << y << "\n";

    return 0;
}
