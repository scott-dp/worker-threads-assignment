//
// Created by scott on 23.01.2025.
//
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <mutex>
#include <atomic>

#ifndef OVING2_WORKERS_H
#define OVING2_WORKERS_H

using namespace std;

class Workers {
public:
    Workers(int numThreads);
    void start();
    void post(void (*threadTask)());
    void join();
    //void post_timeout();

private:
    int numThreads;
    vector<thread> threads;
    atomic<int> currentThread = 0;
    mutex waitForVacantThreadMutex;
    condition_variable cv;

};


#endif //OVING2_WORKERS_H
