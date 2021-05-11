//
// Created by ksawery.karwacki on 5/11/2021.
//

#ifndef DINING_PHILOSOPHERS_WAITER_H
#define DINING_PHILOSOPHERS_WAITER_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include "Chopstick.h"

class Waiter {
public:
    Waiter(int count, std::vector<Chopstick> &chopsticks, std::vector<Philosopher> &philosophers);
    void requestChopstick(int philosopherNumber, bool isRight = false);
    void returnChopsticks(int philosopherNumber);
private:
    void returnChopstick(int number);
    std::vector<Chopstick>& chopsticks;
    std::vector<Philosopher>& philosophers;
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};


#endif //DINING_PHILOSOPHERS_WAITER_H
