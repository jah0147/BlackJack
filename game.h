//
// Created by jacob_howard on 9/21/2022.
//

#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
using namespace std;
#include "config.h"

#include "globals.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <array>

class game {
public:
    bool playGame();
    void gameOver();
    unsigned int dealCard();
    void initialDeal();
    int caclulateCardTotal(int highLow, vector<int> hand);
    bool checkForBust(int who);
    void playerTurn();
    void dealerTurn();
    //may use these to simplify game code
    //void playerTurn();
    //void dealerTurn();
    void payPlayer();
    bool checkForAce(vector<int> hand);

    //player actions
    void bet();
    void hit(int who);

    //may not be inplimented yet
    //void doubleDown();
    //void split();

    void calculateWinner();

private:
    //Just trust these values (max value card is 11 and min is 1)
    const unsigned int maxCard = 10;
    const unsigned int minCard = 2;

    bool Continue = true;
    unsigned int playerBetTemp; //temp value to verify userBet

    vector<int> playerHand; //technically the max amount of cards you could draw is 21
    vector<int> playerHandSplit; //players second hand if they choose to split
    vector<int> dealerHand; //technically the max amount of cards you could draw is 21
    int playerCardTotalHigh = 0;
    int playerCardTotalHighSplit = 0;
    int playerCardTotalLow = 0; //In the event of an ace
    int playerCardTotalLowSplit = 0; //In the event of an ace
    int playerCardTotalSplitHigh = 0;
    int playerCardTotalSplitLow = 0;
    int dealerCardTotalHigh = 0;
    int dealerCardTotalLow = 0;

    int playerBestHand = 0;
    int playerBestHandSplit = 0;
    int dealerBestHand = 0;

    bool playerBust = false;
    bool playerBustSplit = false;
    bool dealerBust = false;
    bool playerBlackJack = false;
    bool dealerBlackJack = false;
    bool bSplit = false;
    bool bSplitTurn = false;
    bool bStay = false;
    bool playerWon = false;
    bool playerWonSplit = false;
    bool tie = false;

    bool playerTurn2 = false;

    enum gameEnums
    {
        BET = 1,
        GAMEUI = 2,
    };

    enum cardTotal
    {
        HIGH = 1,
        LOW = 2
    };
    enum playerDecision
    {
        HIT = 1,
        STAY = 2,
        DOUBLEDOWN = 3,
        SPLIT = 4
    };
    enum Who
    {
        PLAYER = 1,
        DEALER = 2,
        SPLITHAND = 3
    };
};


#endif //BLACKJACK_GAME_H
