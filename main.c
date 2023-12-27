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

int askCol(int max) {
    int e, input, tmp;
    do {
        printf("donnez un numéro de colonne: ");
        e = scanf("%d", &input);
        do {
            tmp = getchar();
        } while (tmp != EOF && tmp != '\n');
        printf("%d\n", input);
    } while (e != 1 || input < 1 || input > max);
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
    Game game = makeGame(6, 7);
    int ia[2];
    Player winner = NULL;
    Player player;
    int col, row, win;
    askIA(ia);
    for (int turn = 0; turn < game->maxTurn; turn++) {
        player = game->players[game->currentPlayer];
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        displayGame(game);
        printf("\n\n\n\n");
        printf("Au tour du joueur ");
        displayPlayer(player);
        if (ia[turn % 2]) {
            printf(" (ia).\n");
            col = minimax(game, min(17, game->maxTurn - turn - 1));
            row = getRow(game, col);
            place(game, col, row);
            printf("%d\n", col);
        }
        else {
            printf(".\n");
            do {
                col = askCol(game->width) - 1;
                row = getRow(game, col);
                printf("%d,%d\n",col, row);
            } while (row == -1);
            place(game, col, row);
        }
        if (isPosAWin(game, col, row)) {
            winner = player;
            break;
        }
    }
    showWin(game);
    if (winner == NULL)
        printf("Égalité.\n");
    else {
        printf("Victoire du joueur ");
        displayPlayer(winner);
        printf(" !\n");
    }
}

int main() {
    gammeLoop();
    return 0;
}