#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <mutex>

extern std::vector<std::string> primeResults;

bool isPrime(int n);
void threadFunction(int threadId, int range, int extra);
void showTime(std::string &formattedTime);
bool readConfig(const std::string &filename, int &threadCount, int &range);

#endif