#include <iostream>
#include "Workers.h"

using namespace std;

int main() {
    //Workers worker_threads(4);
    Workers event_loop(1);
    //worker_threads.start(); // Create 4 internal threads
    event_loop.start(); // Create 1 internal thread
    /**worker_threads.post([] {
        cout << "Hello from thread 1" << "\n";
        cout << "thread 1 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 2" << "\n";
        cout << "thread 2 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 3" << "\n";
        cout << "thread 3 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 4" << "\n";
        cout << "thread 4 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 5" << "\n";
        cout << "thread 5 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 6" << "\n";
        cout << "thread 6 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 7" << "\n";
        cout << "thread 7 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 8" << "\n";
        cout << "thread 8 finishing..." << "\n";
    });
    worker_threads.post([] {
        cout << "Hello from thread 9" << "\n";
        cout << "thread 9 finishing..." << "\n";
    });
    event_loop.post([] {
        cout << "Hello from event loop thread 1" << "\n";
        cout << "event loop thread 1 finishing..." << "\n";
    });
    event_loop.post([] {
        cout << "Hello from event loop thread 2" << "\n";
        cout << "event loop thread 2 finishing..." << "\n";
    });*/
    event_loop.post_timeout([] {
        cout << "Hello from A!" << endl;
    }, 2000);
    event_loop.post_timeout([] {
        cout << "Hello from B!" << endl;
    }, 1000);
    //worker_threads.join(); // Calls join () on the worker threads
    event_loop.join();
    return 0;
}
