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

Game copyGame(Game g) {
    Game new;
    new.np = g.np;
    new.g = (Player*)malloc(42 * sizeof(Player));
    if (new.g == NULL) {
        fprintf(stderr, "Erreur malloc dans 'copyGame'\n");
        exit(2);
    }
    for (int i=0; i < 42; i++) {
        new.g[i] = g.g[i];
    }
    return new;
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
    // if (col > 6 || col < 0) {
    //     fprintf(stderr, "Erreur, mauvaise collonne dans 'placeInCol': %d\n", col);
    //     exit(1);
    // }
    for (int y=5; y >= 0; y--) {
        i = y*7 + col;
        if (g.g[i] == g.np) {
            g.g[i] = p;
            return y;
        }
    }
    return -1;
}

void undo(Game g, int x, int y) {
    g.g[x + y * 7] = g.np;
}

int isPosAWin(Game g, int x, int y) {
    int i = x + y * 7;
    Player pion = g.g[i];
    if (pion == g.np)
        return 0;
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
    int i;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t╔═════╤═════╤═════╤═════╤═════╤═════╤═════╗\n");
    for (int y=0; y < 6; y++) {
        printf("\t\t║");
        for (int x=0; x < 7; x++) {
            i = y * 7 + x;
            if (isPosAWin(g, x, y))
                printf("  %s\033[1m\033[5m%c\033[0m  ", g.g[i]->color, g.g[i]->pion);
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

Array makeArray() {
    // printf("in make\n");
    Array a;
    a = (Array)calloc(SIZE, sizeof(Data));
    if (!a) {
        fprintf(stderr, "Erreur calloc dans 'makeArray'\n");
        exit(2);
    }
    // printf("out make\n");
    return a;
}

int search(Array a, unsigned long id, int *found) {
    // printf("in search\n");
    int i = id % SIZE;
    *found = 0;
    while (a[i] && a[i]->id != id) {
        // printf("%d\n", i);
        i = (i + 1) % SIZE;
    }
    if (a[i] && a[i]->id == id)
        *found = 1;
    // printf("out search\n");
    return i;
}

void insert(Array a, unsigned long id, int score) {
    // printf("in insert\n");
    Data *d;
    int found;
    int i = search(a, id, &found);
    if (found) {
        if (a[i]->score < score) 
            a[i]->score = score;
        // printf("out insert\n");
        return;
    }
    d = (Data*)malloc(sizeof(Data));
    if (!d) {
        fprintf(stderr, "Erreur malloc dans 'insert'\n");
        exit(2);
    }
    d->id = id;
    d->score = score;
    a[i] = d;
    // printf("out insert\n");
}

void freeArray(Array a) {
    for (int i = 0; i < SIZE; i ++) {
        free(a[i]);
    }
    free(a);
}

void printArray(Array a) {
    // printf("in print\n");
    for (int i = 0; i < SIZE; i ++) {
        if (a[i])
            printf("(%lu, %d) ", a[i]->id, a[i]->score);
    }
    printf("\n");
    // printf("out print\n");
}
