#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pion;
    char color[10];
} PionColor, *Player;

typedef struct {
    Player* g;
    Player np;
} Game;

typedef struct {
    unsigned long id;
    int score;
} Data;

typedef Data **Array;

Player makePlayer(char pion, char color[]);

Game makeGame();
Game copyGame(Game g);
void displayGame(Game g);
int placeInCol(Game g, int col, Player p);
void undo(Game g, int x, int y);
int isPosAWin(Game g, int x, int y);
void showWin(Game g);

Array makeArray();
int search(Array a, unsigned long id, int *found);
void insert(Array a, unsigned long id, int score);
void freeArray(Array a);
void printArray(Array a);