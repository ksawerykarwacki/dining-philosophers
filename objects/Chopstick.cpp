//
// Created by ksawery.karwacki on 5/11/2021.
//

#include "Chopstick.h"

Chopstick::Chopstick(int number) {
    this->number = number;
    this->usedBy = nullptr;
}

Philosopher *Chopstick::getUsedBy() {
    return usedBy;
}

void Chopstick::setUsedBy(Philosopher *usedBy) {
    Chopstick::usedBy = usedBy;
}

std::string Chopstick::getName() {
    return "Chopstick no. " + std::to_string(this->number);
}
