//
// Created by jacob_howard on 9/21/2022.
//

#include "game.h"
#include "console.h"
using namespace std;
console console;

bool game::playGame() {
    //initialize values
    Continue = true;
    playerHand.clear(); //technically the max amount of cards you could draw is 21
    playerHandSplit.clear();
    dealerHand.clear(); //technically the max amount of cards you could draw is 21
    playerCardTotalHigh = 0;
    playerCardTotalLow = 0; //In the event of an ace
    playerCardTotalLowSplit = 0;
    playerCardTotalSplitHigh = 0;
    playerCardTotalSplitLow = 0;
    dealerCardTotalHigh = 0;
    dealerCardTotalLow = 0;
    playerBestHand = 0;
    playerBestHandSplit = 0;
    dealerBestHand = 0;
    playerBust = false;
    playerBustSplit = false;
    dealerBust = false;
    playerBlackJack = false;
    dealerBlackJack = false;
    bSplit = false;
    bSplitTurn = false;
    bStay = false;
    playerWon = false;
    playerWonSplit = false;
    tie = false;
    playerTurn2 = false;

    if (chipBalance > 0)
    {
        bet();
        initialDeal();
        playerCardTotalHigh = caclulateCardTotal(HIGH, playerHand);
        playerCardTotalLow = caclulateCardTotal(LOW, playerHand);
        dealerCardTotalHigh = caclulateCardTotal(HIGH, dealerHand);
        dealerCardTotalLow = caclulateCardTotal(LOW, dealerHand);

        if (playerCardTotalHigh == 21)
        {
            playerBlackJack = true;
            playerWon = true;
        }
        else
        {
            while (((playerCardTotalLow < 21)) && (!bStay) && (!playerBust))
            {
                //print here and get user input
                console.gameUI(GAMEUI, playerCardTotalHigh, playerCardTotalLow,
                                        dealerCardTotalHigh, dealerCardTotalLow,
                                        playerHand, dealerHand, playerHandSplit,
                               bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);

                playerTurn();
                playerTurn2 = true;
            }
            if (bSplit)
            {
                bStay = false;
                playerCardTotalLowSplit = playerHandSplit[0];
                playerCardTotalHighSplit = playerHandSplit[0];
                while (((playerCardTotalLowSplit < 21)) && (!bStay) && (!playerBustSplit))
                {
                    bSplitTurn = true;
                    //print here and get user input
                    console.gameUI(GAMEUI, playerCardTotalHigh, playerCardTotalLow,
                                   dealerCardTotalHigh, dealerCardTotalLow,
                                   playerHand, dealerHand, playerHandSplit,
                                   bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);

                    playerTurn();
                }


            }
            if (!playerBust || !playerBustSplit) //If user did not bust
            {
                dealerTurn();
            }
            else {
                console.bust(PLAYER);
                playerWon = false;
            }
        }
        // check for Dealer BlackJack
        string dummyString;
        //Change this to splashscreen later
        if (playerWon || tie) {
            payPlayer();

        }
        console.displayResults(dealerBestHand, playerBestHand, playerBestHandSplit, (playerWon||tie||playerWonSplit), bSplit);
        cout << "\nContinue? (Y/N): ";
        cin >> dummyString;
        //replace
        if (dummyString != "y") {
            Continue = false;
        }
    }
    else {
        Continue = false;
    }
#ifdef TESTING
#ifdef DELAY
    console.delayInSec(7);
#endif
#endif
    hideDealerCard2 = true; //resets showing dealers full hand
    return Continue; //placeholder for now
}

void game::initialDeal() {
#ifdef ClearConsole
    console.clearConsole();
#endif
    cout << "Dealing Cards..." << endl;
    cout << "|                | 0%" << endl;

    unsigned int card1 = dealCard();
    playerHand.push_back(card1);

#ifdef ClearConsole
    console.clearConsole();
#endif
    cout << "Dealing Cards..."       << endl;
    cout << "|====            | 25%" << endl;


    unsigned int card2 = dealCard();
    dealerHand.push_back(card2);

#ifdef ClearConsole
    console.clearConsole();
#endif
    cout << "Dealing Cards..."       << endl;
    cout << "|========        | 50%" << endl;

    unsigned int card3 = dealCard();
    playerHand.push_back(card3);

#ifdef ClearConsole
    console.clearConsole();
#endif
    cout << "Dealing Cards..."       << endl;
    cout << "|============    | 75%" << endl;

    unsigned int card4 = dealCard();
    dealerHand.push_back(card4);

#ifdef ClearConsole
    console.clearConsole();
#endif
    cout << "Dealing Cards..."       << endl;
    cout << "|================| 100%" << endl;
#ifdef TESTING
    cout << "User card 1: " << playerHand[0] << endl;
    cout << "User card 2: " << playerHand[1] << endl;
    cout << endl;
    cout << "Dealer card 1: " << dealerHand[0] << endl;
    cout << "Dealer card 2: " << dealerHand[1] << endl;
#endif
    //this is for testing, please remove later
#ifdef TESTING2
    playerHand[0] = 10;
    playerHand[1] = 10;
#endif
}

int game::caclulateCardTotal(int highLow,vector<int> hand) {
    unsigned int cardTotal = 0;
    bool AceExists = checkForAce(hand);
    int aceLocation = 0;

    switch (highLow) {
        case HIGH:
            cardTotal = 0;
            for (int i = 0; i <= (hand.size() - 1); i++)
            {
                cardTotal += hand[i];
            }
            if (cardTotal > 21)
            {
                if (AceExists)
                {
                    for (int i=0; i <= (hand.size()-1); i++)
                    {
                        if (hand[i] == 11)
                        {
                            aceLocation = i;
                        }
                    }
                    hand[aceLocation] = 1;
                    cardTotal = 0;
                    for (int i = 0; i <= (hand.size()-1); i++)
                    {
                        cardTotal += hand[i];
                    }
                    if (cardTotal > 21) {
                        AceExists = checkForAce(hand);
                    }
                    else {
                        AceExists = false;
                    }
                }
            }
            break;
        case LOW:
            while (AceExists) {
                for (int i = 0; i <= (hand.size()-1); i++) {
                    if (hand[i] == 11) {
                        aceLocation = i;
                    }
                }
                hand[aceLocation] = 1;
                AceExists = checkForAce(hand);
            }
            cardTotal = 0;
            for (int i = 0; i <= (hand.size()-1); i++)
            {
                cardTotal += hand[i];
            }
            break;
        default:
            cout << "[ERROR] In game.calculateCardTotal()";
            break;
    }
    return cardTotal;
}

unsigned int game::dealCard() {
//#ifdef DELAY //we do not want to disable this with the config.h file as it will break functionality
    console.delayInSec(1);
//#endif
    srand(time(nullptr)); //Randomize seed initialization
    unsigned int card = minCard + (rand()%maxCard); //choses number between 2 and 11

#ifdef TESTING
    cout << "Random card delt:" << card << endl;
#endif

    return card;
}

void game::bet() {
    console.gameUI(BET, 0, 0, 0, 0, playerHand, dealerHand, playerHandSplit); //playerhand and dealerhand are not used here but included to satisfy args
    cout << "\nBet: ";
    cin >> playerBetTemp;

    if ((playerBetTemp%10) != 0 || (playerBetTemp == 0)) //If user bet is not an increment of 10 or bets zero
    {
        cout << "Please only bet in increments of 10!" << endl;
        cout << "Please try again..." << endl;
        console.delayInSec(3);
        bet();
    }
    else if (chipBalance < playerBetTemp) //If user does not have enough to bet amount
    {
        cout << "You do not have enough to bet that ammount!" << endl;
        cout << "Please type in a new bet ammount..." << endl;
        bet();
    }
    else
    {
        playerBet = playerBetTemp; //stores user bet for later if a win
        chipBalance = chipBalance - playerBet; //takes away chip balance
    }

#ifdef TESTING
    cout << "Player bet amount: " << playerBet << endl;
    cout << "New chip balance: " << chipBalance << endl;
#ifdef DELAY
    console.delayInSec(1);
#endif
#endif
}

void game::hit(int who) {
    unsigned int card = dealCard();
    switch (who)
    {
        case PLAYER:
            if (!bSplitTurn)
            {
                playerHand.push_back(card);
                playerCardTotalHigh = caclulateCardTotal(HIGH, playerHand);
                playerCardTotalLow = caclulateCardTotal(LOW, playerHand);
                console.gameUI(GAMEUI,
                               playerCardTotalHigh, playerCardTotalLow,
                               dealerCardTotalHigh, dealerCardTotalLow, playerHand, dealerHand, playerHandSplit,
                               bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);
            } else
            { //if we are on split hand
                playerHandSplit.push_back(card);
                playerCardTotalHighSplit = caclulateCardTotal(HIGH, playerHandSplit);
                playerCardTotalLowSplit = caclulateCardTotal(LOW, playerHandSplit);
                console.gameUI(GAMEUI,
                               playerCardTotalHighSplit, playerCardTotalLowSplit,
                               dealerCardTotalHigh, dealerCardTotalLow, playerHandSplit, dealerHand, playerHandSplit,
                               bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);
            }
            break;
        case DEALER:
            dealerHand.push_back(card);
            dealerCardTotalHigh = caclulateCardTotal(HIGH, dealerHand);
            dealerCardTotalLow = caclulateCardTotal(LOW, dealerHand);
            console.gameUI(GAMEUI,
                           playerCardTotalHigh, playerCardTotalLow,
                           dealerCardTotalHigh, dealerCardTotalLow, playerHand, dealerHand, playerHandSplit,
                           bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);
            if (bSplit)
            {
                console.gameUI(GAMEUI,
                               playerCardTotalHighSplit, playerCardTotalLowSplit,
                               dealerCardTotalHigh, dealerCardTotalLow, playerHandSplit, dealerHand, playerHandSplit,
                               bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);
            }
            break;

        default:
            cout << "[ERROR] In game.hit()";
            break;
    }
}

bool game::checkForAce(vector<int> hand) {
    bool isAce = count(hand.begin(), hand.end(), 11);
    return isAce;
}

bool game::checkForBust(int who) {
    bool bust;
    switch (who)
    {
        case PLAYER:
            if (!bSplitTurn) {
                playerCardTotalHigh = caclulateCardTotal(HIGH, playerHand);
                playerCardTotalLow = caclulateCardTotal(LOW, playerHand);


                if (playerCardTotalHigh > 21) {
                    if (playerCardTotalLow > 21) {
                        bust = true;
                        playerCardTotalLow = 0;
                    } else {
                        bust = false;
                    }
                } else {
                    bust = false;
                }
            } else
            {
                playerCardTotalHighSplit = caclulateCardTotal(HIGH, playerHandSplit);
                playerCardTotalLowSplit = caclulateCardTotal(LOW, playerHandSplit);


                if (playerCardTotalHighSplit > 21) {
                    if (playerCardTotalLowSplit > 21) {
                        bust = true;
                        playerCardTotalLowSplit = 0;
                    } else {
                        bust = false;
                    }
                } else {
                    bust = false;
                }
            }
            break;
        case DEALER:
            dealerCardTotalHigh = caclulateCardTotal(HIGH, dealerHand);
            dealerCardTotalLow = caclulateCardTotal(LOW, dealerHand);

            if (dealerCardTotalHigh > 21)
            {
                if (dealerCardTotalLow > 21)
                {
                    bust = true;
                }
                else
                {
                    bust = false;
                }
            }
            else {
                bust = false;
            }
            break;
        default:
            cout << "[ERROR] In game.checkForBust()";
            break;
    }
    return bust;
}

void game::playerTurn() {
    int userInput = 0;
                cout << "[1] HIT" << endl;
                cout << "[2] STAY" << endl;
#ifdef DoubleDown
                if (chipBalance >= playerBet)
                {
                    if (!playerTurn2)
                    {
                        cout << "[3] DOUBLE DOWN" << endl;
                    }
                }
#endif
#ifdef Split
                if (playerHand[0] == playerHand[1]) {
                    if (!playerTurn2)
                    {
                        if (chipBalance >= playerBet)
                        {
                            cout << "[4] SPLIT" << endl;
                        }
                    }
                    }
#endif
                cout << "\nInput" << endl;
                cin >> userInput;
                int tempHand1 = 0;
                switch (userInput) {
                    case HIT:
                        hit(PLAYER);
                        if (bSplitTurn)
                        {
                            playerBustSplit = checkForBust(PLAYER); //check if bust
                        }
                        else {
                            playerBust = checkForBust(PLAYER); //check if bust
                        }
                        break;

                    case STAY:
                        bStay = true;
                        //hideDealerCard2 = false;
                        break;
#ifdef DoubleDown
                    case DOUBLEDOWN:
                        if (chipBalance >= chipBalance)
                        {
                            if (!playerTurn2) {
                                chipBalance -= playerBet;
                                playerBet += playerBet;
                                hit(PLAYER);
                                playerBust = checkForBust(PLAYER); //check if bust
                                bStay = true;
                            }
                            else
                            {
                                cout << "CANNOT DOUBLE DOWN" << endl;
                            }
                        }
                        break;
#endif

                    case SPLIT:
                        if (!bSplit) {
                            if (playerHand[0] == playerHand[1]) {
                                if (!playerTurn2) {
                                    if (chipBalance >= playerBet) {
                                        bSplit = true;
                                        tempHand1 = playerHand[0];
                                        playerHand.clear();
                                        playerHandSplit.clear();
                                        playerHand.push_back(tempHand1);
                                        playerHandSplit.push_back(tempHand1);
                                        playerCardTotalLow = playerHand[0];
                                        playerCardTotalHigh = playerHand[0];
                                        chipBalance = chipBalance - playerBet;
                                        //playerBet += playerBet;
                                    }
                                } else {
                                    cout << "CANNOT SPLIT" << endl;
                                }
                            }else {
                                cout << "CANNOT SPLIT" << endl;
                            }
                        } else
                        {
                            cout << "CANNOT SPLIT" << endl;
                        }
                        break;

                    default:
                        cout << "[ERROR] In playGame switch statement";
                        break;
                }
}

void game::dealerTurn() {
    calculateWinner(); //used for generating player best hand
    hideDealerCard2 = false;
    console.gameUI(GAMEUI, playerCardTotalHigh, playerCardTotalLow,
                   dealerCardTotalHigh, dealerCardTotalLow,
                   playerHand, dealerHand, playerHandSplit,
                   bSplitTurn, playerCardTotalHighSplit, playerCardTotalLowSplit);
    if (dealerCardTotalHigh == 21)
    {
        dealerBlackJack = true;
    }
    else {
        while ((dealerCardTotalHigh < 17) && ((dealerCardTotalHigh < playerBestHand) || (dealerCardTotalHigh < playerBestHandSplit)) && !dealerBust) {
            hit(DEALER);
            console.delayInSec(1);
            dealerBust = checkForBust(DEALER);
        }
        if (dealerCardTotalHigh > 21 && dealerCardTotalLow < 17)
        {
            while (dealerCardTotalLow < 17) {
                hit(DEALER);
                console.delayInSec(1);
                dealerBust = checkForBust(DEALER);
            }
        }
        if (dealerBust) {
            console.bust(DEALER);
            calculateWinner(); //for math-ing
            playerWon = true;
            if (bSplit)
            {
                playerWonSplit = true;
            }
        } else {
            calculateWinner();
        }
    }
}

void game::payPlayer() {
    if (playerBlackJack && dealerBlackJack)
    {
        chipBalance += playerBet;
    }
    else if (playerBlackJack && !dealerBlackJack)
    {
        chipBalance += (playerBet * 3); //tripple players bet
    }
    else if (bSplit) //Checks if player split their hand
    {
        if (tie)
        {
            chipBalance += playerBet;
        }
        if (playerWon && playerWonSplit)
        {
            chipBalance += (playerBet * 2); //double players bet
        } else if (playerWon)
        {
            chipBalance += (playerBet);
        } else if (playerWonSplit)
        {
            chipBalance += (playerBet);
        }
    }
    else if (tie)
    {
        chipBalance += playerBet;
    }
    else if (playerWon) //non-split hand check
    {
        chipBalance += (playerBet * 2); //double players bet
    }
}

void game::calculateWinner() {
    //calculate playerBestHand
    if (playerCardTotalHigh <= 21)
    {
        playerBestHand = playerCardTotalHigh;
    } else{
        playerBestHand = playerCardTotalLow;
    }
    if (bSplit)
    {
        if (playerCardTotalHighSplit <= 21)
        {
            playerBestHandSplit = playerCardTotalHighSplit;
        } else{
            playerBestHandSplit = playerCardTotalLowSplit;
        }
    }
    //////////////////////////////////////////
    if (dealerCardTotalHigh <= 21)
    {
        dealerBestHand = dealerCardTotalHigh;
    } else {
        dealerBestHand = dealerCardTotalLow;
    }
    //////////////////////////////////////////
    if (bSplit) //if player split their hand
    {
        if ((playerBestHand == dealerBestHand) && (playerBestHandSplit == dealerBestHand))
        {
            playerWon = true; //this is set so the correct amount gets paid to the player if they end up with a tie for both hands
        }
        else
        {
            if (playerBestHand == dealerBestHand || playerBestHandSplit == dealerBestHand)
            {
                tie = true;
            }
            if (playerBestHand > dealerBestHand)
            {
                playerWon = true;
            }
            if (playerBestHandSplit > dealerBestHand)
            {
                playerWonSplit = true;
            }
        }
    }
    else { //non split
        if (playerBestHand == dealerBestHand) {
            tie = true;
        } else if (playerBestHand > dealerBestHand) {
            playerWon = true;
        } else {
            playerWon = false;
            tie = false;
        }
    }


}