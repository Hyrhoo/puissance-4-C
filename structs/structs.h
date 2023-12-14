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

typedef struct maillon {
    unsigned long id;
    int score;
    struct maillon *next;
    struct maillon *last;
} Maillon;

typedef struct {
    Maillon* start;
    Maillon* end;
} List;


Player makePlayer(char pion, char color[]);

Game makeGame();
Game copyGame(Game g);
void displayGame(Game g);
int placeInCol(Game g, int col, Player p);
void undo(Game g, int x, int y);
int isPosAWin(Game g, int x, int y);
void showWin(Game g);

List makeList();
Maillon* search(List l, unsigned long id, int *found);
void insert(List *l, unsigned long id, int score);
void freeList(List *l);
void printList(List l);