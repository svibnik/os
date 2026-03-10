#include "thread_func.h"
#include <iostream>
#include <climits>

DWORD WINAPI min_max(LPVOID param) {
    ThreadData* data = static_cast<ThreadData*>(param);
    const std::vector<int>& arr = *data->arr;
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        Sleep(7);
    }
    *data->min = min_val;
    *data->max = max_val;
    std::cout << "Min = " << min_val << ", Max = " << max_val << std::endl;
    return 0;
}

DWORD WINAPI average(LPVOID param) {
    ThreadData* data = static_cast<ThreadData*>(param);
    const std::vector<int>& arr = *data->arr;
    int sum = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
        Sleep(12);
    }
    *data->avg = static_cast<double>(sum) / arr.size();
    std::cout << "Average = " << *data->avg << std::endl;
    return 0;
}