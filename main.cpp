#include <iostream>
#include <windows.h>
#include "Workers.h"

using namespace std;

int main() {
    Workers worker_threads(4);
    Workers event_loop(1);
    worker_threads.start(); // Create 4 internal threads
    event_loop.start(); // Create 1 internal thread
    worker_threads.post([] {
        cout << "Hello from thread 1" << "\n";
        Sleep(3000);
        cout << "thread 1 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 2" << "\n";
        Sleep(3000);
        cout << "thread 2 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 3" << "\n";
        Sleep(3000);
        cout << "thread 3 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 4" << "\n";
        Sleep(3000);
        cout << "thread 4 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 5" << "\n";
        Sleep(3000);
        cout << "thread 5 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 6" << "\n";
        Sleep(3000);
        cout << "thread 6 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 7" << "\n";
        Sleep(3000);
        cout << "thread 7 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 8" << "\n";
        Sleep(3000);
        cout << "thread 8 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 9" << "\n";
        Sleep(3000);
        cout << "thread 9 finishing..." << "\n";
    });
    event_loop.post([] {
        // Task C
        // Might run in parallel with task A and B
    });
    event_loop.post([] {
        // Task D
        // Will run after task C
        // Might run in parallel with task A and B
    });
    worker_threads.join(); // Calls join () on the worker threads
    event_loop.join();
    return 0;
}
