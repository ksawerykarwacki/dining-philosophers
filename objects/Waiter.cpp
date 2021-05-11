//
// Created by ksawery.karwacki on 5/11/2021.
//

#include "Waiter.h"
#include "Philosopher.h"
Waiter::Waiter(int count, std::vector<Chopstick> &chopsticks, std::vector<Philosopher> &philosophers) : count(count), chopsticks(chopsticks), philosophers(philosophers) {}

void Waiter::requestChopstick(int philosopherNumber, bool isRight) {
    std::unique_lock<std::mutex> lock(mtx);
    Philosopher& philosopher = philosophers[philosopherNumber];
    auto number = isRight ? (philosopher.getNumber()+1) % chopsticks.size() : philosopher.getNumber();
    while(count == 0 || (count == 1 && !isRight && chopsticks[number].getUsedBy() != nullptr)) {
        //wait on the mutex until notify is called
        cv.wait(lock);
    }
    chopsticks[number].setUsedBy(&philosopher);
    count--;
}

void Waiter::returnChopstick(int number) {
    std::unique_lock<std::mutex> lock(mtx);
    chopsticks[number].setUsedBy(nullptr);
    count++;
    //notify the waiting thread
    cv.notify_one();
}

void Waiter::returnChopsticks(int philosopherNumber) {
    returnChopstick(philosopherNumber);
    returnChopstick((philosopherNumber + 1) % chopsticks.size());
}
