#ifndef THREAD_FUNC_H
#define THREAD_FUNC_H

#include <windows.h>
#include <vector>

struct ThreadData {
    const std::vector<int>* arr;
    int* min;
    int* max;
    double* avg;
};
DWORD WINAPI min_max(LPVOID param);
DWORD WINAPI average(LPVOID param);

#endif