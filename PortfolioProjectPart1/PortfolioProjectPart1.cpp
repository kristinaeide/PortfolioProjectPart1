// PortfolioProjectPart1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

// The mutex protects the shared Boolean value.
mutex counterMutex;

// The condition variable allows thread two to wait.
condition_variable counterCondition;

// This value tracks whether thread one has finished.
bool firstThreadFinished = false;

// Thread one counts upward from 0 to 20.
void countUp()
{
    cout << "Thread 1 is counting up:" << endl;

    for (int number = 0; number <= 20; number++)
    {
        cout << number << endl;

        // This delay makes the output easier to follow.
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    {
        lock_guard<mutex> lock(counterMutex);
        firstThreadFinished = true;
    }

    // Wake thread two after thread one reaches 20.
    counterCondition.notify_one();
}

// Thread two waits and then counts downward.
void countDown()
{
    {
        unique_lock<mutex> lock(counterMutex);

        counterCondition.wait(lock, []()
            {
                return firstThreadFinished;
            });
    }

    cout << endl;
    cout << "Thread 2 is counting down:" << endl;

    for (int number = 20; number >= 0; number--)
    {
        cout << number << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main()
{
    cout << "C++ Concurrency Counter Application" << endl;
    cout << "-----------------------------------" << endl;

    // Create the two counter threads.
    thread firstCounter(countUp);
    thread secondCounter(countDown);

    // Wait for both threads to finish before closing.
    firstCounter.join();
    secondCounter.join();

    cout << endl;
    cout << "Both counter threads have finished." << endl;

    return 0;
}

