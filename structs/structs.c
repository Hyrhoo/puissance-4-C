#include "structs.h"

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

Game makeGame() {
    Game g;
    g.np = makePlayer(' ', "");
    g.g = (Player*)malloc(42 * sizeof(Player));
    if (g.g == NULL) {
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
        exit(2);
    }
    for (int i=0; i < 42; i++) {
        g.g[i] = g.np;
    }
    return g;
}

void displayGame(Game g) {
    int i;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t╔═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n");
    for (int y=0; y < 6; y++) {
        i=y*7;
        printf("\t\t║  %s%c\033[0m  │  %s%c\033[0m  │  %s%c\033[0m  │  %s%c\033[0m  │  %s%c\033[0m  │  %s%c\033[0m  │  %s%c\033[0m  ║\n", g.g[i]->color, g.g[i]->pion, g.g[i+1]->color, g.g[i+1]->pion, g.g[i+2]->color, g.g[i+2]->pion, g.g[i+3]->color, g.g[i+3]->pion, g.g[i+4]->color, g.g[i+4]->pion, g.g[i+5]->color, g.g[i+5]->pion, g.g[i+6]->color, g.g[i+6]->pion);
        if (y != 5)
            printf("\t\t╟─────┼─────┼─────┼─────┼─────┼─────┼─────╢\n");
    }
    printf("\t\t╚═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n");
    printf("\t\t   1     2     3     4     5     6     7   \n");
    printf("\n\n\n\n\n");
}

int placeInCol(Game g, int col, Player p) {
    int i;
    if (col > 6 || col < 0) {
        fprintf(stderr, "Erreur, mauvaise collonne dans 'placeInCol': %d\n", col);
        exit(1);
    }
    for (int y=5; y >= 0; y--) {
        i = y*7 + col;
        if (g.g[i] == g.np) {
            g.g[i] = p;
            return y;
        }
    }
    return -1;
}

int isPosAWin(Game g, int x, int y) {
    int i = x + y * 7;
    Player pion = g.g[i];
    if (pion == g.np)
        return 0;
    //printf("debug(%d, %d)\n", x, y);
    int test[] = {-1, -6, -8, -7};
    int xtest[] = {-1, 1, -1, 0};
    int cons, dep, xdep, last, next;
    int a, b, c, d;
    for (int j=0; j < 4; j++) {
        cons = 1;
        for (int delta=-1; delta < 2; delta+=2) {
            dep = test[j] * delta;
            xdep = xtest[j] * delta;
            last = i;
            next = i + dep;
            while ((next >= 0 || next < 42) && !((last%7 == 0) && (xdep == -1) || (last%7 == 6) && (xdep == 1))) {
                if (g.g[next] == pion) {
                    cons++;
                    //printf("debug(i %d (%d, %d), last %d (%d, %d), next %d (%d, %d), dep %d, xdep %d, pion %c, g.g[next] %c)\n", i, i%7, i/7, last, last%7, last/7, next%7, next/7, next, dep, xdep, pion->pion, g.g[next]->pion);
                    if (cons == 4)
                        return 1;
                }
                else 
                    break;
                last = next;
                next += dep;
            }
        }
    }
    return 0;
}

void showWin(Game g) {
    // \033[0;32m
    int i;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t╔═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n");
    for (int y=0; y < 6; y++) {
        printf("\t\t║");
        for (int x=0; x < 7; x++) {
            i = y * 7 + x;
            if (isPosAWin(g, x, y))
                printf("  \033[0;32m%c\033[0m  ", g.g[i]->pion);
            else printf("  %s%c\033[0m  ", g.g[i]->color, g.g[i]->pion);
            if (x != 6)
                printf("│");
        }
        printf("║\n");
        if (y != 5)
            printf("\t\t╟─────┼─────┼─────┼─────┼─────┼─────┼─────╢\n");
    }
    printf("\t\t╚═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n");
    printf("\t\t   1     2     3     4     5     6     7   \n");
    printf("\n\n\n\n\n");
}