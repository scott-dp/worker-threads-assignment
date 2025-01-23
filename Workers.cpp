//
// Created by scott on 23.01.2025.
//

#include "Workers.h"
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <mutex>

using namespace std;

void Workers::post(void (*threadTask)()) {
    unique_lock<mutex> lock(waitForVacantThreadMutex);
    while (currentThread == numThreads) {
        cv.wait(lock); //Unlocks waitForVacantThreadMutex, and locks again when woken up
    }
    //Here there now is vacant worker thread
    currentThread++;//increase the number of used threads
    threads.emplace_back([this, threadTask]() {
        threadTask();
        this->currentThread--;
        this->cv.notify_all();
    });
}

void Workers::join() {
    for (auto &t : threads) {
        t.join();
    }
}

Workers::Workers(int numThreads) {
    this->numThreads = numThreads;
}

void Workers::start() {
    threads.reserve(numThreads);
}
