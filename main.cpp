#include <iostream>
#include "header.h"

int main() {
    unsigned int seed = static_cast<unsigned int>(time(nullptr)); //random number generator
    srand(seed);

    char dungeon[MAX_SIZE][MAX_SIZE];
    int playerCurrent[2];
    int playerNew[2];

    bool lose;
    bool win;
    bool keepPlaying = false;

    std::cout << "Welcome to my dungeon crawler!\n" << std::endl;

    do {
        //Define initial start for game
        createDungeon(dungeon, MAX_SIZE, TRAPS, TREASURES, EXIT, PLAYING, playerCurrent);
        displayDungeon(dungeon, MAX_SIZE);
        //Game loop. Continue until the player either falls into a trap or gets to the exit
        do {
            getMove(playerCurrent, playerNew);
            //check to see if player lost
            lose = checkLose(dungeon, playerNew);
            //Check to see if player won
            win = checkWin(dungeon, playerNew);
            //Check to see if player found treasure
            checkTreasure(dungeon, playerNew);
            updateDungeon(dungeon, MAX_SIZE, playerCurrent, playerNew);
        } while (!win && !lose);
        if (lose) {
            std::cout << "You lost!" << std::endl;
        }
        if (win) {
            std::cout << "You win!" << std::endl;
        }
        keepPlaying = playAgain();
    } while (keepPlaying);

    return 0;
}