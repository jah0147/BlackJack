//
// Created by jacob_howard on 9/21/2022.
//

#ifndef BLACKJACK_CONSOLE_H
#define BLACKJACK_CONSOLE_H
#include "config.h"

#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using  namespace std;

class console {
public:

    void welcomeMsg();
    void printArt();
    void selectBalance();
    void gameUI(int UI,
                int playerTotalHigh, int playerTotalLow,
                int dealerTotalHigh, int dealerTotalLow,
                vector<int> playerHand, vector<int> dealerHand);
    void bust(int who);
    void displayResults(int dealerTotal, int playerTotal, bool won);
    void clearConsole();
    void delayInSec(int seconds);

private:
    bool inputNotInBounds = false;
    unsigned int userInput;
    enum UI
    {
        BET = 1,
        GAMEUI = 2,
    };
    enum WHO
    {
        PLAYER = 1,
        DEALER = 2,
    };
};

#endif //BLACKJACK_CONSOLE_H
