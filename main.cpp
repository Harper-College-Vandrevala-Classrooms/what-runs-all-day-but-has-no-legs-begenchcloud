#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Timer {
private:
    chrono::time_point<chrono::system_clock> start_time;
    chrono::time_point<chrono::system_clock> stop_time;
    bool is_running;
    int elapsed_time;

public:
    Timer() : is_running(false), elapsed_time(0) {}

    void start() {
        if (!is_running) {
            start_time = chrono::system_clock::now();
            is_running = true;
        }
    }

    void stop() {
        if (is_running) {
            stop_time = chrono::system_clock::now();
            elapsed_time += chrono::duration_cast<chrono::seconds>(stop_time - start_time).count();
            is_running = false;
        }
    }

    int elapsed() const {
        if (is_running) {
            auto current_time = chrono::system_clock::now();
            return elapsed_time + chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
        } else {
            return elapsed_time;
        }
    }

    void reset() {
        is_running = false;
        elapsed_time = 0;
    }
};

int main() {
    Timer timer;

    cout << "Timer is initialized. Elapsed time: " << timer.elapsed() << " seconds\n";

    cout << "Starting timer...\n";
    timer.start();

    this_thread::sleep_for(chrono::seconds(3));

    cout << "Stopping timer...\n";
    timer.stop();

    cout << "Elapsed time after stopping: " << timer.elapsed() << " seconds\n";

    cout << "Restarting timer...\n";
    timer.start();

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Stopping timer again...\n";
    timer.stop();

    cout << "Total elapsed time: " << timer.elapsed() << " seconds\n";

    cout << "Resetting timer...\n";
    timer.reset();

    cout << "Elapsed time after reset: " << timer.elapsed() << " seconds\n";

    return 0;
}
