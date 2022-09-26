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
    dealerHand.clear(); //technically the max amount of cards you could draw is 21
    playerCardTotalHigh = 0;
    playerCardTotalLow = 0; //In the event of an ace
    dealerCardTotalHigh = 0;
    dealerCardTotalLow = 0;
    playerBestHand = 0;
    dealerBestHand = 0;
    playerBust = false;
    dealerBust = false;
    playerBlackJack = false;
    dealerBlackJack = false;
    bStay = false;
    playerWon = false;
    tie = false;

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
                                        playerHand, dealerHand);
                int userInput;
                cout << "[1] HIT" << endl;
                cout << "[2] STAY" << endl;
                cout << "\nInput" << endl;
                cin >> userInput;
                switch (userInput)
                {
                    case HIT:
                        hit(PLAYER);
                        playerBust = checkForBust(PLAYER);
                        break;

                    case STAY:
                        bStay = true;
                        hideDealerCard2 = false;
                        break;

                        //not implimented yet
//                            case DOUBLEDOWN:
//                                //doubleDown();
//                                break;
//
//                            case SPLIT:
//                                //split();
//                                break;

                    default:
                        cout << "[ERROR] In playGame switch statement";
                        break;
                }
            }
            if (!playerBust) //If user did not bust
            {
                calculateWinner(); //used for generating player best hand
                if (dealerCardTotalHigh == 21)
                {
                    dealerBlackJack = true;
                }
                else {
                    while ((dealerCardTotalHigh < 17 && dealerCardTotalHigh < playerBestHand) && !dealerBust) {
                        hideDealerCard2 = false;
                        console.gameUI(GAMEUI, playerCardTotalHigh, playerCardTotalLow,
                                       dealerCardTotalHigh, dealerCardTotalLow,
                                       playerHand, dealerHand);
                        hit(DEALER);
                        console.delayInSec(1);
                        dealerBust = checkForBust(DEALER);
                    }
                    if (dealerCardTotalHigh > 21)
                    {
                        while (dealerCardTotalLow < 17) {
                            hit(DEALER);
                            console.delayInSec(1);
                            dealerBust = checkForBust(DEALER);
                        }
                    }
                    if (dealerBust) {
                        console.bust(DEALER);
                        playerWon = true;
                    } else {
                        calculateWinner();
                    }
                }
            }
            else {
                playerWon = false;
            }
        }
        // check for Dealer BlackJack
        string dummyString;
        //Change this to splashscreen later
        if (playerWon || tie) {
            payPlayer();

        }
        console.displayResults(dealerBestHand, playerBestHand, (playerWon||tie));
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
    console.gameUI(BET, 0, 0, 0, 0, playerHand, dealerHand); //playerhand and dealerhand are not used here but included to satisfy args
    cout << "\nBet: ";
    cin >> playerBetTemp;

    if ((playerBetTemp%10) != 0) //If user bet is not an increment of 10
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
            playerHand.push_back(card);
            playerCardTotalHigh = caclulateCardTotal(HIGH, playerHand);
            playerCardTotalLow = caclulateCardTotal(LOW, playerHand);
            console.gameUI(GAMEUI,
                           playerCardTotalHigh, playerCardTotalLow,
                           dealerCardTotalHigh, dealerCardTotalLow, playerHand, dealerHand);
            break;
        case DEALER:
            dealerHand.push_back(card);
            dealerCardTotalHigh = caclulateCardTotal(HIGH, dealerHand);
            dealerCardTotalLow = caclulateCardTotal(LOW, dealerHand);
            console.gameUI(GAMEUI,
                           playerCardTotalHigh, playerCardTotalLow,
                           dealerCardTotalHigh, dealerCardTotalLow, playerHand, dealerHand);
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
            playerCardTotalHigh = caclulateCardTotal(HIGH, playerHand);
            playerCardTotalLow = caclulateCardTotal(LOW, playerHand);

            if (playerCardTotalHigh > 21)
            {
                if (playerCardTotalLow > 21)
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

void game::payPlayer() {
    if (tie)
    {
        chipBalance += playerBet;
    }
    else if (playerBlackJack && dealerBlackJack)
    {
        chipBalance += playerBet;
    }
    else if (playerBlackJack && !dealerBlackJack)
    {
        chipBalance += (playerBet * 3); //double players bet
    }
    else if (playerWon)
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
    //////////////////////////////////////////
    if (dealerCardTotalHigh <= 21)
    {
        dealerBestHand = dealerCardTotalHigh;
    } else {
        dealerBestHand = dealerCardTotalLow;
    }
    //////////////////////////////////////////
    if (playerBestHand == dealerBestHand)
    {
        tie = true;
    }
    else if (playerBestHand > dealerBestHand)
    {
        playerWon = true;
    } else {
        playerWon = false;
    }

}