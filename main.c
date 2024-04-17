#include "minimax/minimax.h"
#include "time.h"

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

void printTime(double seconds) {
    int min, sec = seconds;
    if (seconds >= 60) {
        min = sec % 60;
        sec = sec / 60;
        printf("%d min and %d sec\n", min, sec);
    } else printf("%d sec\n", sec);
}

void gammeLoop() {
    Game game = makeGame(6, 7);
    int ia[2];
    Player winner = NULL;
    Player player;
    Dict save = makeDict();
    int col, row, win;
    playSequance(game, "3 3 3 3 3 3 2 1 5 4 4 4 4 4");
    askIA(ia);
    while (game->currentTurn < game->maxTurn) {
        player = game->players[game->currentPlayer];
        // printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        displayGame(game);
        printf("\n\n\n\n");
        printf("Au tour du joueur ");
        displayPlayer(player);
        if (ia[game->currentTurn % 2]) {
            printf(" (ia).\n");
            time_t start = time(NULL);
            col = minimax(game, min(42, game->maxTurn - game->currentTurn - 1), save);
            time_t end = time(NULL);
            row = getRow(game, col);
            printTime(difftime(end, start));
        }
        else {
            printf(".\n");
            do {
                col = askCol(game->width) - 1;
                row = getRow(game, col);
                printf("%d,%d\n", col, row);
            } while (row == -1);
        }
        place(game, col, row);
        savePlay(game, col);
        if (isPosAWin(game, col, row)) {
            winner = player;
            break;
        }
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    showWin(game);
    printf("\n\n\n\n");
    if (winner == NULL)
        printf("Égalité.\n");
    else {
        printf("Victoire du joueur ");
        displayPlayer(winner);
        printf(" !\n");
    }
    printf("%s\n", game->plays);
}

int main() {
    gammeLoop();
    return 0;
}