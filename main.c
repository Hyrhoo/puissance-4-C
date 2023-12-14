#include "minimax/minimax.h"

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int varInTab(int var, int tab[], int nb) {
    for (int i = 0; i < nb; i++) {
        if (var == tab[i]) 
            return 1;
    }
    return 0;
}

int askCol() {
    int e, input, tmp;
    do {
        printf("donnez un numéro de collone: ");
        e = scanf("%d", &input);
        do {
            tmp = getchar();
        } while (tmp != EOF && tmp != '\n');
    } while (e != 1 || input < 1 || input > 7);
    return input;
}

void askIA(int ia[]) {
    int e, tmp, input, values[] = {1, 2, 3, 4};
    do {
        printf("Comment voulez-vous jouer ?\n - 1) Joueur contre Joueur\n - 2) Joueur en premier, IA en second\n - 3) IA en premier, Joueur en second\n - 4) IA contre IA\n");
        e = scanf("%d", &input);
        do {
            tmp = getchar();
        } while (tmp != EOF && tmp != '\n');
    } while (e != 1 || !varInTab(input, values, 4));
    if (input == 1) {
        ia[0] = 0; ia[1] = 0; return;
    }
    if (input == 2) {
        ia[0] = 0; ia[1] = 1; return;
    }
    if (input == 3) {
        ia[0] = 1; ia[1] = 0; return;
    }
    if (input == 4) {
        ia[0] = 1; ia[1] = 1; return;
    }
}

void gammeLoop() {
    Game g = makeGame();
    Player players[] = {makePlayer('x', "\033[0;31m"), makePlayer('o', "\033[0;34m")};
    int ia[2];
    Player winner = NULL;
    Player player;
    int col, row, win;
    askIA(ia);
    for (int turn = 0; turn < 42; turn++) {
        displayGame(g);
        player = players[turn % 2];
        printf("Au tour du joueur %s%c\033[0m", player->color, player->pion);
        if (ia[turn % 2]) {
            printf(" (ia).\n");
            col = minimax(g, min(4, 41-turn), player, players[(turn+1) % 2]);
            row = placeInCol(g, col, player);
            printf("%d\n", col);
        }
        else {
            printf(".\n");
            do {
                col = askCol() - 1;
                row = placeInCol(g, col, player);
            } while (row == -1);
        }
        if (isPosAWin(g, col, row)) {
            winner = player;
            break;
        }
    }
    showWin(g);
    if (winner == NULL)
        printf("Égalité.\n");
    else
        printf("Victoire du joueur %s%c\033[0m!\n", winner->color, winner->pion);
}

int main() {
    // Game g = makeGame(), g2;
    // Player p = makePlayer('x', "\033[0;31m");
    // placeInCol(g, 1, p);
    // displayGame(g);
    // undo(g, 1, 5);
    // displayGame(g);
    // g2 = copyGame(g);
    // displayGame(g2);
    // placeInCol(g2, 1, p);
    // displayGame(g);
    // displayGame(g2);
    gammeLoop();
    // List l = makeList();
    // insert(&l, 500UL, 2);
    // printList(l);
    // insert(&l, 100UL, 2);
    // printList(l);
    // insert(&l, 200UL, 2);
    // printList(l);
    // insert(&l, 1000UL, 2);
    // insert(&l, 2000UL, 2);
    // insert(&l, 500UL, 3);
    // insert(&l, 600UL, 2);
    // insert(&l, 700UL, 2);
    // insert(&l, 300UL, 2);
    // printList(l);
    return 0;
}