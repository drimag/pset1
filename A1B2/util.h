#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <mutex>

bool isPrime(int n);
void threadFunction(int threadId, int max);
void showTime();
bool readConfig(const std::string &filename, int &threadCount, int &range);

#endif