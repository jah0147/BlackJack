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
                vector<int> playerHand, vector<int> dealerHand, vector<int> playerHandSplit,
                bool split = false, int playerTotalHighSplit = 0, int playerTotalLowSplit = 0); //default values so we do not always have to use them
    void bust(int who);
    void displayResults(int dealerTotal, int playerTotal, int playerTotalSplit = 0, bool won = false, bool split = false);
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
