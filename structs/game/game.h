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
    Player players[3];
} *Game;

Game makeGame(int height, int width);
void displayGame(Game game);
int getRow(Game game, int col);
// int placeInCol(Game game, int col, Player p);
void changePlayer(Game game);
void place(Game game, int x, int y);
void undo(Game game, int x, int y);
bool isPosAWin(Game game, int x, int y);
void showWin(Game game);