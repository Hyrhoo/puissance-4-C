#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../game/game.h"

// #define SIZE 632281415
#define SIZE 500000000

typedef struct {
    unsigned long id;
    int score;
} Data, **Dict;

Dict makeDict();
unsigned long hashf(Game game);
int search(Dict dict, unsigned long id, bool *found);
void insert(Dict dict, unsigned long id, int score);
void freeDict(Dict dict);
void printDict(Dict dict);