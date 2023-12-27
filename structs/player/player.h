#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pion;
    char color[10];
} PionColor, *Player;

Player makePlayer(char pion, char color[]);
void displayPlayer(Player p);