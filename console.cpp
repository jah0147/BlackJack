//
// Created by jacob_howard on 9/21/2022.
//

#include "console.h"
#include "globals.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;

/*
 * Function: welcomeMsg
 * Description: Displays a welcome message
 */
void console::welcomeMsg() {
    cout << "--------------------------------------------------------------------" << endl;
    cout << "|                       WELCOME TO BLACKJACK                       |" << endl;
    cout << "|                      Created by Jacob Howard                     |" << endl;
    cout << "--------------------------------------------------------------------" << endl;
#ifdef DELAY
    delayInSec(3);
#endif
}
/*
 * Function: printArt
 * Description: Prints art from a text file to easily display art.
 */
void console::printArt() {
    std::string line; //string that holds the line of a text file
    //std::ifstream textFile("textFiles/art/art.txt", std::ios::in); //file creation
    std::ifstream textFile("art.txt", std::ios::in); //file creation

    if(textFile.is_open()) //checking if file was opened
    {
        while(getline(textFile, line))
        {
            //std::getline(textFile, line);
            std::cout << line << "\n";
        }
    } else {
        std::cout <<"Unable to load art from text file..." <<std::endl; //Prints if file was not opened
    }
    textFile.close();
}

/*
 * Function: selectBalance
 * Description: Used to displa possible starting balances and allows user to select amount.
 */
void console::selectBalance() {
#ifdef ClearConsole
    clearConsole(); //should clear the console
#endif
    cout << "--------------------SELECT STARTING CHIP BALANCE--------------------" << endl;
    cout << "       [1]     100" << endl;
    cout << "       [2]     1000" << endl;
    cout << "       [3]     10000" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    if (inputNotInBounds)
    {
        cout << "That is not a valid selection!" << endl;
    }
    cout << "\nInput: ";
    cin >> userInput;
#ifdef ClearConsole
    clearConsole(); //should clear the console in terminal window
#endif
    //If user inputs a number not in range
    while ((userInput > 3) || (userInput < 1))
    {
        inputNotInBounds = true;
        selectBalance();
    }
    inputNotInBounds = false;
    //sets balance
    switch (userInput) {
        case 1:
            chipBalance = 100;
            break;
        case 2:
            chipBalance = 1000;
                    break;
        case 3:
            chipBalance = 10000;
            break;
        default:
            cout << "[ERROR]Selecting chip balance" << endl;
            break;

    }
}

void console::bust(int who)
{
            cout << "--------------------------------------------------------------------" << endl;
    switch (who)
    {
        case PLAYER:
            cout << "|                            YOU BUSTED                            |" << endl;
            break;
        case DEALER:
            cout << "|                           DEALER BUSTED                          |" << endl;
            break;
    }
    cout << "--------------------------------------------------------------------" << endl;
    delayInSec(2);
}

/*
 * Function: gameUI
 * Descrition: Displays the game user-interface in the console
 */
void console::gameUI(int UI,
                     int playerTotalHigh, int playerTotalLow,
                     int dealerTotalHigh, int dealerTotalLow,
                     vector<int> playerHand, vector<int> dealerHand)
{
    switch (UI)
    {
        case BET:
#ifdef ClearConsole
            clearConsole();
#endif
            cout << "--------------------------PLACE YOUR BETS--------------------------" << endl;
            cout << "             Note: Bets can only be in increments of 10            " << endl;
            cout << "-------------------------------------------------------------------" << endl;
            cout << "\n Chip Balance: " << chipBalance << endl;
            break;
        case GAMEUI:
#ifdef ClearConsole
            clearConsole();
#endif
            cout << "-------------------------------------------------------------------" << endl;
            cout << "Dealers Hand: ";
            if (hideDealerCard2) { //this value is changed outside the class
                cout << " ";
                cout << "[" << dealerHand[0] << "] ";
                cout << "[*]";
                cout << endl;
            } else {
                for (int i = 0; i < dealerHand.size(); i++)
                {
                    cout << " ";
                    cout << "[" << dealerHand[i] << "]";
                }
                //spacing
                cout << endl;
                cout << endl;
                if (dealerTotalHigh == dealerTotalLow) {
                    cout << "Dealers card total: " << dealerTotalHigh;
                }
                else if (dealerTotalHigh <= 21) {
                    cout << "Dealers card total: " << dealerTotalHigh << " or " << dealerTotalLow << endl;
                } else {
                    cout << "Dealers card total: " << dealerTotalLow;
                }
            }
            //spacing
            cout << endl;
            cout << endl;
            cout << "Your Hand: ";
            for (int i = 0; i < playerHand.size(); i++)
            {
                cout << " ";
                cout << "[" << playerHand[i] << "]";
            }
            //spacing
            cout << endl;
            cout << endl;

            if (playerTotalHigh == playerTotalLow) {
                cout << "Your card total: " << playerTotalHigh;
            }
            else if (playerTotalHigh <= 21) {
                cout << "Your card total: " << playerTotalHigh << " or " << playerTotalLow << endl;
            } else {
                cout << "Your card total: " << playerTotalLow;
            }
            cout << endl;
            cout <<  "\nChip Balance: " << chipBalance << endl;
            cout << "-------------------------------------------------------------------" << endl;
            break;
        default:
            cout << "[ERROR] In game UI" << endl;
            break;
    }
}

void console::displayResults(int dealerTotal, int playerTotal, bool won)
{
//#ifdef ClearConsole
//    clearConsole();
//#endif
    cout << "-------------------------------------------------------------------" << endl;
    cout << "                DEALERS CARD TOTAL: " << dealerTotal << endl;
    cout << endl;
    cout << "                 YOUR CARD TOTAL: " << playerTotal << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;
    if (won) {
        cout <<             "       YOU WON!" << endl;
    }
    else {
        cout <<             "       YOU LOST!" << endl;
    }
}

/*
 * Function: clearConsole
 * Description: This function should clear console messages on Windows PCs.
 */
void console::clearConsole()
{
    system("CLS");

}
/*
 * Function: delayInSec
 * Description: Creates a delay until next console msg should be displayed.
 */
void console::delayInSec(int sec) {
    sleep_until(system_clock::now() + seconds(sec));
}