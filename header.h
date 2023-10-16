#pragma once

const int MAX_SIZE = 15;
const int TRAPS = 10;
const int TREASURES = 10;
const int EXIT = 1;
const int PLAYING = 1;

int randRange(int low, int high);
void createDungeon(char dungeon[MAX_SIZE][MAX_SIZE], int size, int traps, int treasures, int exit, int playing, int playerCurrent[]);
void displayDungeon(const char dungeon[MAX_SIZE][MAX_SIZE], int size);
void getMove(const int playerCurrent[], int playerNew[]);
bool checkLose(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]);
bool checkWin(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]);
void checkTreasure(const char dungeon[MAX_SIZE][MAX_SIZE], const int playerNew[]);
void updateDungeon(char dungeon[MAX_SIZE][MAX_SIZE], int size, int playerCurrent[], int playerNew[]);
bool playAgain();