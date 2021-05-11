//
// Created by ksawery.karwacki on 5/11/2021.
//

#ifndef DINING_PHILOSOPHERS_CHOPSTICK_H
#define DINING_PHILOSOPHERS_CHOPSTICK_H

class Philosopher;

class Chopstick {
public:
    Chopstick(int number);
    Philosopher *getUsedBy();
    void setUsedBy(Philosopher *usedBy);
private:
    int number;
    Philosopher *usedBy;
};


#endif //DINING_PHILOSOPHERS_CHOPSTICK_H
