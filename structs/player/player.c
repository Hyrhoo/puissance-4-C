#include "player.h"

Player makePlayer(char pion, char color[]) {
    Player p;
    p = (Player)malloc(sizeof(PionColor));
    if (p == NULL) {
        fprintf(stderr, "Erreur malloc dans 'makePlayer'\n");
        exit(2);
    }
    p->pion = pion;
    strcpy(p->color, color);
    return p;
}

void displayPlayer(Player p) {
    printf("%s%c\033[0m", p->color, p->pion);
}