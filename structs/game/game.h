#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../player/player.h"

typedef struct game {
    int height;
    int width;
    int **board;
    int *colHeight;
    int currentTurn;
    int maxTurn;
    int currentPlayer;
    int *test;
    Player players[3];
    char *plays;
} *Game;

Game makeGame(int height, int width);
void displayGame(Game game);
int getRow(Game game, int col);
void changePlayer(Game game);
void place(Game game, int x, int y);
void savePlay(Game game, int play);
void undo(Game game, int x, int y);
void playSequance(Game game, char sec[]);
bool isPosAWin(Game game, int x, int y);
void showWin(Game game);