#include <gtest/gtest.h>
#include <windows.h>
#include <vector>
#include "thread_func.h"

TEST(ThreadTest, MinMaxTest) {
    std::vector<int> arr = { 5, 2, 8, 1, 9 };
    int min_val = 0, max_val = 0;
    double avg_val = 0;
    ThreadData data = { &arr, &min_val, &max_val, &avg_val };
    HANDLE hThread = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    EXPECT_EQ(min_val, 1);
    EXPECT_EQ(max_val, 9);
}

TEST(ThreadTest, AverageTest) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    int min_val = 0, max_val = 0;
    double avg_val = 0;
    ThreadData data = { &arr, &min_val, &max_val, &avg_val };
    HANDLE hThread = CreateThread(NULL, 0, average, &data, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    EXPECT_DOUBLE_EQ(avg_val, 3.0);
}

TEST(ThreadTest, BothThreadsTest) {
    std::vector<int> arr = { 3, 7, 2, 9, 5 };
    int min_val = 0, max_val = 0;
    double avg_val = 0;
    ThreadData data = { &arr, &min_val, &max_val, &avg_val };
    HANDLE h1 = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, average, &data, 0, NULL);
    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);
    CloseHandle(h2);
    CloseHandle(h1);
    EXPECT_EQ(min_val, 2);
    EXPECT_EQ(max_val, 9);
    EXPECT_DOUBLE_EQ(avg_val, 5.2);
    for (int& x : arr) {
        if (x == min_val || x == max_val) {
            x = static_cast<int>(avg_val);
        }
    }
    bool hasMin = false, hasMax = false;
    for (int x : arr) {
        if (x == min_val) hasMin = true;
        if (x == max_val) hasMax = true;
    }
    EXPECT_FALSE(hasMin);
    EXPECT_FALSE(hasMax);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}