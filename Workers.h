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
# include <functional>
#include <list>

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
    mutex taskMutex;
    condition_variable cv;
    list<function<void()>> tasks ;
    vector<thread> worker_threads;
    atomic<bool> stopRunning = false;
};


#endif //OVING2_WORKERS_H
