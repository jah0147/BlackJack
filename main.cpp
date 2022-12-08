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
    return 0;
}
