#pragma once
#include <ctime>
#include <iostream>
using namespace std;

using testFunc = void(__stdcall*)();

// 函数func执行count次所用时间
double testTime(testFunc func, int count) {
    clock_t startTime, endTime;
    startTime = clock();
    for (int i = 0; i < count; i++)
        func();
    endTime = clock();
    return  (double)(endTime - startTime) / CLOCKS_PER_SEC;
}