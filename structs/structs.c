#include "structs.h"

Game makeGame() {
    Game g;
    g = (Game)malloc(42 * sizeof(char));
    if (g == NULL) {
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n" );
        exit(2);
    }
    for (int i=0; i < 42; i++) {
        g[i] = ' ';
    }
    return g;
}

void displayGame(Game g) {
    int i;
    printf("\t╔═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n");
    for (int y=0; y < 6; y++) {
        i=y*7;
        printf("\t║  %c  │  %c  │  %c  │  %c  │  %c  │  %c  │  %c  ║\n", g[i], g[i+1], g[i+2], g[i+3], g[i+4], g[i+5], g[i+6]);
        if (y != 5)
            printf("\t╟─────┼─────┼─────┼─────┼─────┼─────┼─────╢\n");
    }
    printf("\t╚═════╧═════╧═════╧═════╧═════╧═════╧═════╝\n");
    printf("\t   1     2     3     4     5     6     7   \n");
}

int placeInCol(Game g, int col, char pion) {
    int i;
    if (col > 6 || col < 0) {
        fprintf(stderr, "Erreur, mauvaise collonne dans 'placeInCol': %d\n", col);
        exit(1);
    }
    for (int y=5; y >= 0; y--) {
        i = y*7 + col;
        if (g[i] == ' ') {
            g[i] = pion;
            return y;
        }
    }
    return -1;
}

int isPosAWin(Game g, int x, int y) {
    int i = x + y * 7;
    char pion = g[i];
    int test[] = {-1, -6, -8, -7};
    int ytest[] = {-1, 0, 0, -1};
    int cons, dep, ydep, last, next;
    int a, b, c, d;
    for (int j=0; j < 4; j++) {
        cons = 1;
        for (int delta=-1; delta < 2; delta+=2) {
            dep = test[j] * delta;
            ydep = ytest[j] * delta;
            last = i;
            next = i + dep;
            while ((next >= 0 || next < 42) && !((last%7 == 0) && (ydep == -1) || (last%7 == 6) && (ydep == 1))) {
                if (g[next] == pion) {
                    cons++;
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