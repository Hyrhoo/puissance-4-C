#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pion;
    char color[10];
}PionColor, *Player;

typedef struct {
    Player* g;
    Player np;
} Game;

Player makePlayer(char pion, char color[]);

Game makeGame();
void displayGame(Game g);
int placeInCol(Game g, int col, Player p);
int isPosAWin(Game g, int x, int y);
void showWin(Game g);