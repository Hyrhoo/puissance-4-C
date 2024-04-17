#include "game.h"

/* 
    \033[0;31m : rouge
    \033[0;32m : vert
    \033[0;33m : jaune
    \033[0;34m : bleu
    \033[0;35m : violet
    \033[0;36m : cyen
*/

Game makeGame(int height, int width) {
    Game game;
    game = (Game)malloc(sizeof(struct game));
    if (game == NULL) {
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
        exit(2);
    }
    game->height = height;
    game->width = width;
    game->currentTurn = 0;
    game->maxTurn = width * height;
    game->board = (int**)malloc(sizeof(int*) * height);
    if (game->board == NULL) {
        // free(game);
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
        exit(2);
    }
    for (int i = 0; i < height; i ++) {
        game->board[i] = (int*)malloc(sizeof(int) * width);
        if (game->board[i] == NULL) {
            // for (i; i >= 0; i --)
            //     free(game->board[i]);
            // free(game->board);
            // free(game);
            fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
            exit(2);
        }
        for (int j = 0; j < width; j ++)
            game->board[i][j] = 0;
    }
    game->colHeight = (int*)malloc(sizeof(int) * width);
    if (game->colHeight == NULL) {
        // for (int i = 0; i < height; i ++)
        //     free(game->board[i]);
        // free(game->board);
        // free(game);
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
        exit(2);
    }
    for (int i = 0; i < width; i ++) {
        game->colHeight[i] = 0;
    }
    game->test = (int*)malloc(sizeof(int) * game->width);
    if (game->test == NULL) {
        fprintf(stderr, "Erreur malloc dans 'makeGame'\n");
        exit(2);
    }
    int cpt = 1;
    game->test[0] = game->width / 2;
    for (int i = 1; i <= game->test[0]; i ++) {
        game->test[cpt] = game->test[0] - i;
        game->test[cpt+1] = game->test[0] + i;
        cpt += 2;
    }
    if (game->width % 2 == 0) game->test[cpt] = 0;
    game->plays = (char*)calloc(game->maxTurn*3, sizeof(char));
    game->players[0] = makePlayer(' ', "");
    game->players[1] = makePlayer('X', "\033[0;36m");
    game->players[2] = makePlayer('0', "\033[0;31m");
    game->currentPlayer = 1;
    return game;
}

void displayGame(Game game) {
    // print ligne haut
    printf("\t\t╔");
    for (int i = 1; i <= game->width; i++) {
        printf("═════");
        if (i != game->width)
            printf("╤");
    }
    printf("╗\n");
    // print board
    for (int y = 0; y < game->height; y ++) {
        // print ligne pion
        printf("\t\t║");
        for (int x = 0; x < game->width; x ++) {
            printf("  ");
            displayPlayer(game->players[game->board[y][x]]);
            printf("  ");
            if (x + 1 != game->width)
                printf("│");
        }
        printf("║\n");
        // print entre lignes
        if (y + 1 != game->height) {
            printf("\t\t╟");
            for (int x = 1; x <= game->width; x ++) {
                printf("─────");
                if (x != game->width)
                    printf("┼");
            }
            printf("╢\n");
        }
    }
    // print ligne bas
    printf("\t\t╚");
    for (int i = 1; i <= game->width; i++) {
        printf("═════");
        if (i != game->width)
            printf("╧");
    }
    printf("╝\n");
    // print numeros
    printf("\t\t ");
    for (int i = 1; i <= game->width; i++) {
        printf("  %d ", i);
        if (i < 10) printf(" ");
        if (i != game->width)
            printf(" ");
    }
    printf("\n");
}

int getRow(Game game, int col) {
    // printf("in getrow\n");
    int row = game->height - game->colHeight[col] - 1;
    // printf("out getrow\n");
    return (row < 0) ? -1 : row;
}

void changePlayer(Game game) {
    // printf("in change\n");
    game->currentPlayer = (game->currentPlayer % 2) + 1;
    // printf("out change\n");
}

void place(Game game, int x, int y) {
    // printf("in place\n");
    // printf("%d %d\n", x, y);
    game->board[y][x] = game->currentPlayer;
    game->currentTurn += 1;
    game->colHeight[x] ++;
    changePlayer(game);
    // printf("out place\n");
}

void savePlay(Game game, int play) {
    char nbr[4];
    if (strlen(game->plays) == 0) {
        sprintf(nbr, "%d", play);
        strcat(game->plays, nbr);
    } else {
        sprintf(nbr, " %d", play);
        strcat(game->plays, nbr);
    }
}

void undo(Game game, int x, int y) {
    game->board[y][x] = 0;
    game->currentTurn -= 1;
    game->colHeight[x] --;
    changePlayer(game);
}

void playSequance(Game game, char sec[]) {
    char nbr[3];
    int col, row, i = 0;
    for (sec; *sec != 0; sec ++) {
        if (*sec == ' ') {
            col = atoi(nbr);
            strcpy(nbr, "\0");
            i = 0;
            row = getRow(game, col);
            place(game, col, row);
            savePlay(game, col);
        } else {
            nbr[i] = *sec;
            i ++;
            nbr[i] = 0;
        }
    }
    col = atoi(nbr);
    row = getRow(game, col);
    place(game, col, row);
    savePlay(game, col);
}

bool isPosAWin(Game game, int x, int y) {
    int nextX, nextY, nb, pion = game->board[y][x];
    // printf("%d %d %d\n", x, y, pion);
    // if (pion == 0) return false;
    if (game->colHeight[x] >= 4 &&
    // if (y <= (game->height - 4) &&
        game->board[y+1][x] == pion &&
        game->board[y+2][x] == pion &&
        game->board[y+3][x] == pion) return true;
    for (int dy = -1; dy <= 1; dy ++) {
        nb = 0;
        for (int dx = -1; dx <= 1; dx += 2) {
            nextX = x + dx;
            nextY = y + dx * dy;
            // printf("%d %d, %d %d\n", nextX, nextY, game->width, game->height);
            while (nextX >= 0 && nextX < game->width && nextY >= 0 && nextY < game->height && game->board[nextY][nextX] == pion) {
                nb ++;
                if (nb >= 3) return true;
                nextX += dx;
                nextY += dx * dy;
                // printf("%d %d\n", nextX, nextY);
            }
        }
    }
    return false;
}

bool showPosWin(Game game, int x, int y) {
    int nextX, nextY, nb, pion = game->board[y][x];
    if (pion == 0) return false;
    for (int dy = -1; dy <= 1; dy ++) {
        nb = 0;
        for (int dx = -1; dx <= 1; dx += 2) {
            nextX = x + dx;
            nextY = y + dx * dy;
            while (nextX >= 0 && nextX < game->width && nextY >= 0 && nextY < game->height && game->board[nextY][nextX] == pion) {
                nb ++;
                if (nb >= 3) return true;
                nextX += dx;
                nextY += dx * dy;
            }
        }
    }
    nb = 0;
    for (int dy = -1; dy <= 1; dy += 2) {
        nextY = y + dy;
        while (nextY >= 0 && nextY < game->height && game->board[nextY][x] == pion) {
            nb ++;
            if (nb >= 3) return true;
            nextY += dy;
        }
    }
    return false;
}

void showWin(Game game) {
    // print ligne haut
    printf("\t\t╔");
    for (int i = 1; i <= game->width; i++) {
        printf("═════");
        if (i != game->width)
            printf("╤");
    }
    printf("╗\n");
    // print board
    for (int y = 0; y < game->height; y ++) {
        // print ligne pion
        printf("\t\t║");
        for (int x = 0; x < game->width; x ++) {
            printf("  %s", game->players[game->board[y][x]]->color);
            if (showPosWin(game, x, y))
                printf("\033[1m\033[5m");
            printf("%c\033[0m  ", game->players[game->board[y][x]]->pion);
            if (x + 1 != game->width)
                printf("│");
        }
        printf("║\n");
        // print entre lignes
        if (y + 1 != game->height) {
            printf("\t\t╟");
            for (int x = 1; x <= game->width; x ++) {
                printf("─────");
                if (x != game->width)
                    printf("┼");
            }
            printf("╢\n");
        }
    }
    // print ligne bas
    printf("\t\t╚");
    for (int i = 1; i <= game->width; i++) {
        printf("═════");
        if (i != game->width)
            printf("╧");
    }
    printf("╝\n");
    // print numeros
    printf("\t\t ");
    for (int i = 1; i <= game->width; i++) {
        printf("  %d ", i);
        if (i < 10) printf(" ");
        if (i != game->width)
            printf(" ");
    }
    printf("\n");
}

