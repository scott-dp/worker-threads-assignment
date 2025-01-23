//
// Created by scott on 23.01.2025.
//
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <mutex>

#ifndef OVING2_WORKERS_H
#define OVING2_WORKERS_H

using namespace std;

class Workers {
public:
    Workers(int numThreads);
private:
    int numThreads;
    vector<thread> threads;
};


#endif //OVING2_WORKERS_H
