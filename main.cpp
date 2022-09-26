#include <iostream>
#include "config.h"
#include "console.h"
#include "game.h"

int main() {
    console console;
    game game;

    bool Continue = true;
#ifdef SPASHSCREEN
    console.printArt();
    console.welcomeMsg();
#endif
    console.selectBalance();
    while (Continue) {
        Continue = game.playGame();
    }
#ifdef TESTING
    int userIn;
    cout << "Press Enter to end game";
    cin >> userIn;
#endif
    return 0;
}
