#include "structs/structs.h"
#include "minimax/minimax.h"

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

void askIA() {
    int e, tmp, input, values[] = {1, 2, 3, 4};
    do {
        printf("Comment voulez-vous jouer ?\n - 1) Joueur contre Joueur\n - 2) Joueur en premier, IA en second\n - 3) IA en premier, Joueur en second\n - 4) IA contre IA\n");
        e = scanf("%d", &input);
        do {
            tmp = getchar();
        } while (tmp != EOF && tmp != '\n');
    } while (e != 1 || varInTab(input, values, 4));
}

void gammeLoop() {
    Game g = makeGame();
    Player players[] = {makePlayer('x', "\033[0;31m"), makePlayer('o', "\033[0;34m")};
    char ia[2];
    Player winner = NULL;
    Player player;
    int col, row, win;
    for (int turn = 0; turn < 42; turn++) {
        displayGame(g);
        player = players[turn % 2];
        printf("Au tour du joueur %s%c\033[0m.\n", player->color, player->pion);
        do {
            col = askCol() - 1;
            row = placeInCol(g, col, player);
        } while (row == -1);
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
    // Game g = makeGame();
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // printf("%d\n", isPosAWin(g, 0, 2));
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // placeInCol(g, 0, 'x');
    // displayGame(g);
    // placeInCol(g, 8, 'x');
    // displayGame(g);
    gammeLoop();
    return 0;
}