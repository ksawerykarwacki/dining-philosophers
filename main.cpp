#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include <curses.h>
#include "objects/Philosopher.h"

using namespace std;
int numberOfPhilosophers = 5;
vector <Philosopher> philosophers;
vector<Chopstick> chopsticks;
bool shouldBreak;

void printProgressBar(int percentage, int lineNumber) {
    int bars = 50 * 1.0 * percentage / 100;
    int spaces = 50 - bars;
    std::string bar = "[";
    bar.append(bars, '#');
    bar.append(spaces, ' ');
    bar.append("] " + std::to_string(percentage) + "%%");
    move(lineNumber, 46);
    attron(COLOR_PAIR(2));
    printw(bar.c_str());
}

void listenForKey()
{
    while(true)
    {
        int c = getch();
        if(c == 27 || c == 113)
        {
            shouldBreak = true;
            break;
        }
    }
}

void writeState() {
    while(true) {
        if(shouldBreak) {
            break;
        }
        clear();
        move(0,0);
        for(int i = 0; i < numberOfPhilosophers; i++) {
            move(i,0);
            attron(COLOR_PAIR(1));
            printw("%s", philosophers[i].getName().c_str());
            attron(COLOR_PAIR(2));
            printw(" is ");
            attron(COLOR_PAIR(3));
            printw("%s", philosophers[i].getStateDescription().c_str());
            auto state = philosophers[i].getState();
            if(state == eating || state == thinking) {
                printProgressBar(philosophers[i].getStateCompleteness(), i);
            }
            refresh();
        }
        for (int i = 0; i < numberOfPhilosophers; i++)
        {
            move(numberOfPhilosophers + 4 + i,0);
            attron(COLOR_PAIR(5));
            printw("%s",chopsticks[i].getName().c_str());
            attron(COLOR_PAIR(2));
            printw(" is used by ");
            attron(COLOR_PAIR(4));
            if(chopsticks[i].getUsedBy() != nullptr)
            {
                printw((*(chopsticks[i].getUsedBy())).getName().c_str());
            }
            else
            {
                printw("-------------");
            }
            refresh();
        }

        for (int i = 0; i < numberOfPhilosophers; i++)
        {
            move(2* (numberOfPhilosophers + 4) + i,0);
            attron(COLOR_PAIR(1));
            printw("%s", philosophers[i].getName().c_str());
            attron(COLOR_PAIR(2));
            printw(" ate ");
            attron(COLOR_PAIR(3));
            printw("%d", philosophers[i].getNumberOfMeals());
            attron(COLOR_PAIR(2));
            printw(" times");
            refresh();
        }

        move(LINES-1, 0);
        std::string text = "  Press q or ESC to exit";
        text.append(COLS-text.length(), ' ');
        attron(COLOR_PAIR(6));
        printw(text.c_str());
        refresh();

        for(int i = 0; i < 500; i++) {
            if(shouldBreak) {
                break;
            }
            usleep(1000);
        }
    }
}



int main() {
    for(int i = 0; i < numberOfPhilosophers; i++)
    {
        chopsticks.emplace_back(i);
    }

    Waiter waiter = Waiter(numberOfPhilosophers, chopsticks, philosophers);

    for(int i = 0; i < numberOfPhilosophers; i++)
    {
        philosophers.emplace_back(i, shouldBreak, waiter);
    }

    initscr();
    timeout(-1);
    noecho();
    raw();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);

    vector <thread> threads;

    threads.emplace_back(&listenForKey);
    threads.emplace_back(&writeState);
    for(int i = 0; i < numberOfPhilosophers; i++)
    {
        threads.emplace_back(&Philosopher::feast, &philosophers[i]);
    }

    for(int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    endwin();
    return 0;
}
