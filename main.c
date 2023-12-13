#include "structs/structs.h"

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

void gammeLoop() {
    Game g = makeGame();
    char players[] = {'x', 'o'};
    char winner = ' ';
    char player;
    int col, row, win;
    for (int turn = 0; turn < 42; turn++) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        displayGame(g);
        printf("\n\n\n\n\n");
        player = players[turn % 2];
        printf("Au tour du joueur %c.\n", player);
        do {
            col = askCol() - 1;
            row = placeInCol(g, col, player);
        } while (row == -1);
        if (isPosAWin(g, col, row)) {
            winner = player;
            break;
        }
    }
    displayGame(g);
    if (winner == ' ')
        printf("Égalité.\n");
    else
        printf("Victoire du joueur %c!\n", winner);
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