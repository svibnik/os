#include <windows.h>
#include <iostream>
#include <vector>
#include <climits>

struct ThreadData {
    const std::vector<int>* arr;
    int* min;
    int* max;
    double* avg;
};
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

int main() {
    try {
        int size;
        std::cout << "Enter array size: ";
        std::cin >> size;
        if (size <= 0) {
            throw std::runtime_error("Size must be positive");
        }
        std::vector<int> arr(size);
        std::cout << "Enter " << size << " integers:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cin >> arr[i];
            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input");
            }
        }
        int min_val = 0, max_val = 0;
        double avg_val = 0;
        ThreadData data = { &arr, &min_val, &max_val, &avg_val };
        HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
        HANDLE hAvg = CreateThread(NULL, 0, average, &data, 0, NULL);
        if (!hMinMax || !hAvg) {
            throw std::runtime_error("Failed to create threads");
        }
        WaitForSingleObject(hMinMax, INFINITE);
        WaitForSingleObject(hAvg, INFINITE);
        CloseHandle(hMinMax);
        CloseHandle(hAvg);
        for (int& x : arr) {
            if (x == min_val || x == max_val) {
                x = static_cast<int>(avg_val);
            }
        }
        std::cout << "Result array: ";
        for (int x : arr) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}