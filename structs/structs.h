#include <stdio.h>
#include <stdlib.h>

typedef char* Game;

Game makeGame();
void displayGame(Game g);
int placeInCol(Game g, int col, char pion);
