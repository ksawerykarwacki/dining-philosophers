//
// Created by ksawery.karwacki on 5/11/2021.
//

#include <unistd.h>
#include <iostream>
#include <string>
#include "Philosopher.h"
#include "Waiter.h"

Philosopher::Philosopher(int number, const bool &shouldBreak, Waiter& waiter) : shouldBreak(shouldBreak), waiter(waiter) {
    this->number = number;
    this->state = 0;
    this->stateCompleteness = 0;
    this->numberOfMeals = 0;
}

void Philosopher::feast() {
    while(true) {
        if(this->shouldBreak){
            break;
        }
        this->setState(waitingForLeftChopstick);
        this->waiter.requestChopstick(this->number);
        this->setState(waitingForRightChopstick);
        this->waiter.requestChopstick(this->number, true);
        this->setState(eating);
        wait();
        this->numberOfMeals++;
        this->waiter.returnChopsticks(this->number);
        this->setState(thinking);
        wait();
    }
}

int Philosopher::getState() const {
    return state;
}

void Philosopher::setState(int state) {
    Philosopher::state = state;
}

int Philosopher::getNumber() const {
    return number;
}

void Philosopher::setNumber(int number) {
    Philosopher::number = number;
}

std::string Philosopher::getName() {
    return "Philosopher " + std::to_string(this->getNumber());
}

double Philosopher::getRandomDelay(double min, double max) {
    double result = (double)rand() / RAND_MAX;
    return (min + result * (max - min)) * 1000000;
}

void Philosopher::wait() {
    stateCompleteness = 0;

    double value = getRandomDelay(1.5, 4);
    auto steps = value / 400000 +1 ;
    auto stepDuration = value / steps;

    for(int i = 0; i < steps; i++)
    {
        if(shouldBreak)
        {
            break;
        }
        usleep(stepDuration);
        stateCompleteness = 1.0 * (i + 1) / steps * 100;
    }
}

std::string Philosopher::getStateDescription() {
    switch(this->state) {
        case waitingForLeftChopstick:
            return "waiting for left chopstick";
        case waitingForRightChopstick:
            return "waiting for right chopstick";
        case eating:
            return "eating";
        case thinking:
            return "thinking";
        default:
            return "dead";
    }
}

int Philosopher::getStateCompleteness() const {
    return stateCompleteness;
}

int Philosopher::getNumberOfMeals() const {
    return numberOfMeals;
}
