//
// Created by scott on 23.01.2025.
//

#include <mutex>
#include <Windows.h>
# include <iostream>
# include <sys/epoll.h>
# include <sys/timerfd.h>
# include <vector >
#include "Workers.h"

using namespace std;

Workers::Workers(int numThreads) {
    //Constructor
    this->numThreads = numThreads;
}

void Workers::post(void (*threadTask)()) {
    unique_lock<mutex> lock(taskMutex);
    tasks.emplace_back(threadTask);
    cv.notify_one();
}

void Workers::join() {
    //Join all threads
    stopRunning = true;
    for (auto &t : worker_threads) {
        cv.notify_one();
        t.join();
    }
}

void Workers::start() {
    for (int i = 0; i < numThreads; ++i) {
        worker_threads.emplace_back([this, i] {
            while(true) {
                function<void()> task;
                {
                    unique_lock<mutex> lock(this->taskMutex);
                    while (tasks.empty()) {
                        if (stopRunning) return;
                        cv.wait(lock);
                    }
                    //Now there is at least one task in tasks
                    task = *tasks.begin(); // Copy task for later use
                    tasks.pop_front();
                }
                task();
            }
        });
    }
}

void Workers::post_timeout(void (*threadTask)(), int timeout) {
    epoll_sleep(timeout);
    unique_lock<mutex> lock(taskMutex);
    tasks.emplace_back(threadTask);
    cv.notify_one();
}

void Workers::epoll_sleep(int timeoutMilliSeconds) {
    int epoll_fd = epoll_create1(0);
    epoll_event timeout;
    timeout.events = EPOLLIN;
    timeout.data.fd = timerfd_create(CLOCK_MONOTONIC , 0);
    itimerspec ts;
    int ms = timeoutMilliSeconds;
    ts.it_value.tv_sec = ms / 1000; // Delay before initial event
    ts.it_value.tv_nsec = (ms % 1000) * 1000000; // Delay before initial event
    ts.it_interval.tv_sec = 0; // Period between repeated events after initial delay , 0: disabled
    ts.it_interval.tv_nsec = 0; // Period between repeated events after initial delay , 0: disabled
    timerfd_settime(timeout.data.fd, 0, &ts, nullptr );
    // Add timeout to epoll so that it is monitored by epoll_wait :
    epoll_ctl(epoll_fd , EPOLL_CTL_ADD , timeout.data.fd, &timeout );
    vector <epoll_event > events(128); // Max events to process at once
    while ( true ) {
        cout << " waiting for events " << endl;
        auto event_count = epoll_wait(epoll_fd , events.data(), events.size(), -1);
        for (int i = 0; i < event_count; i++) {
            cout << " event fd: " << events[i].data.fd << endl;
            if (events[i].data.fd == timeout.data.fd) {
                // Remove timeout from epoll so that it is no longer monitored by epoll_wait :
                epoll_ctl(epoll_fd , EPOLL_CTL_DEL , timeout.data.fd , nullptr );
                return;
            }
        }
    }
}
