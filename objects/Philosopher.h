//
// Created by ksawery.karwacki on 5/11/2021.
//

#ifndef DINING_PHILOSOPHERS_PHILOSOPHER_H
#define DINING_PHILOSOPHERS_PHILOSOPHER_H

#include <string>
#include "Waiter.h"

class Philosopher {
public:
    Philosopher(int number, const bool &shouldBreak, Waiter &waiter);
    void feast();
    int getState() const;
    void setState(int state);
    int getNumber() const;
    void setNumber(int number);
    std::string getName();
    std::string getStateDescription();

    int getStateCompleteness() const;

    int getNumberOfMeals() const;

private:
    void wait();
    double getRandomDelay(double min, double max);
    const bool& shouldBreak;
    Waiter& waiter;
    int number;
    int state;
    int stateCompleteness;
    int numberOfMeals;
};

enum States {
    waitingForLeftChopstick = 1,
    waitingForRightChopstick = 2,
    eating = 3,
    thinking = 4,
    waitingForOthers = 5
};

#endif //DINING_PHILOSOPHERS_PHILOSOPHER_H
