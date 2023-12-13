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
            return 1;
        }
    }
    return 0;
}