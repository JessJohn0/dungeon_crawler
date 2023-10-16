#include <iostream>
#include "header.h"

int randRange(int low, int high) {
    return rand() % (high - low + 1) + low;
    //Pick a random number in between a high number and a low number
}

void createDungeon(char dungeon[MAX_SIZE][MAX_SIZE], int size, int traps, int treasures, int exit, int playing, int playerCurrent[]) {
    //clear the dungeon
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) dungeon[i][j] = '.';
    }
    //PLace traps
    //going to count down the number of traps
    for (int t = 0; t < traps; t++) {
        int x = randRange(0, size - 1);
        int y = randRange(0, size - 1);

        //if space is not available, do the for loop over again
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = '#';
        }
        else {
            t--;
        }
    }
    //Place treasures
    //going to count down the number of treasures
    for (int s = 0; s < treasures; s++) {
        int x = randRange(0, size - 1);
        int y = randRange(0, size - 1);

        //if space is not available, do the for loop over again
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = '$';
        }
        else {
            s--;
        }
    }
    //Place exit
    for (int e = 0; e < exit; e++) {
        int x = randRange(0, size - 1);
        int y = randRange(0, size - 1);

        //if space is not available, do the for loop over again
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = 'X';
        }
        else {
            e--;
        }
    }
    //Place player
    for (int p = 0; p < playing; p++) {
        int x = randRange(0, size - 1);
        int y = randRange(0, size - 1);

        //if space is not available, do the for loop over again
        if (dungeon[x][y] == '.') {
            dungeon[x][y] = '@';
            playerCurrent[0] = x;
            playerCurrent[1] = y;
        }
        else {
            p--;
        }
    }
}

void displayDungeon(const char dungeon[MAX_SIZE][MAX_SIZE], int size) {
    //pass in and display the dungeon
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << dungeon[col][row];
        }
        std::cout << std::endl;
    }
}

void getMove(const int playerCurrent[], int playerNew[]) {
    //playerCurrent has information, playerNew is empty

    char move;
    bool valid_input;

    do {
        valid_input = true;
        std::cout << "\nWhich direction would you like to move? " << std::endl;
        std::cout << "Type 'U' for up, 'D' for down, 'R' for right, or 'L' for left." << std::endl;
        std::cin >> move;
        move = toupper(move);

        if (move != 'U' && move != 'D' && move != 'L' && move != 'R') {
            std::cout << "Invalid entry, please try again." << std::endl;
            valid_input = false;
            std::cin.ignore(100, '\n');
        }

        else if ((move == 'U' && playerCurrent[1] == 0) || (move == 'D' && playerCurrent[1] == (MAX_SIZE - 1))
            || (move == 'L' && playerCurrent[0] == 0) || (move == 'R' && playerCurrent[0] == (MAX_SIZE - 1))) {
            std::cout << "Error: moving there would move you outside of the dungeon. Try again.\n" << std::endl;
            valid_input = false;
            std::cin.ignore(100, '\n');
        }
        else if (move == 'U' && playerCurrent[1] != 0) {
            playerNew[0] = playerCurrent[0];
            playerNew[1] = playerCurrent[1] - 1;
        }
        else if (move == 'D' && playerCurrent[1] != (MAX_SIZE - 1)) {
            playerNew[0] = playerCurrent[0];
            playerNew[1] = playerCurrent[1] + 1;
        }
        else if (move == 'L' && playerCurrent[0] != 0) {
            playerNew[0] = playerCurrent[0] - 1;
            playerNew[1] = playerCurrent[1];
        }
        else if (move == 'R' && playerCurrent[0] != (MAX_SIZE - 1)) {
            playerNew[0] = playerCurrent[0] + 1;
            playerNew[1] = playerCurrent[1];
        }
    } while (!valid_input);


}

bool checkLose(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]) {
    //see if the move is onto a trap. Return true if into trap and false if not.

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (dungeon[i][j] == '#') {
                if (i == playerNew[0] && j == playerNew[1]) {
                    std::cout << "\nYou fell into a trap!" << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkWin(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]) {
    //see if the move is onto the exit. True if into trap and false if not.
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (dungeon[i][j] == 'X') {
                if (i == playerNew[0] && j == playerNew[1]) {
                    std::cout << "\nYou found the exit!" << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}

void checkTreasure(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]) {

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (dungeon[i][j] == '$') {
                if (i == playerNew[0] && j == playerNew[1]) {
                    std::cout << "\nYou found gold!" << std::endl;
                }
            }
        }
    }

}

void updateDungeon(char dungeon[MAX_SIZE][MAX_SIZE], int size, int playerCurrent[], int playerNew[]) {
    //Clear the old player spot and place the new player
    int x, y;
    x = playerNew[0];
    y = playerNew[1];
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (dungeon[i][j] == '@') {
                dungeon[i][j] = '.';
            }
            if (dungeon[i][j] != '@' && i == playerNew[0] && j == playerNew[1]) {
                dungeon[i][j] = '@';
                playerCurrent[0] = playerNew[0];
                playerCurrent[1] = playerNew[1];
            }
        }
    }
    //display new dungeon
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << dungeon[col][row];
        }
        std::cout << std::endl;
    }

}

bool playAgain() {
    //See if the players want to play again
    //Ask if want to play again
    //Validate answer
    //Return answer

    bool valid_input;
    bool playing_again = false;
    char answer;

    do {
        valid_input = true;
        std::cout << "\nWould you like to play again (y/n)?" << std::endl;
        std::cin >> answer;

        if (answer == 'n' || answer == 'N') {
            std::cout << "Goodbye!" << std::endl;
        }
        else if (answer == 'y' || answer == 'Y') {
            std::cout << "You have decided to play again." << std::endl;
            playing_again = true;
        }
        else {
            std::cout << "You have entered an invalid input, try again." << std::endl; //The user will be asked to enter in acceptable input until they do so
            valid_input = false;
            std::cin.ignore(100, '\n');
        }
    } while (!valid_input);

    return playing_again;
}