#include "minimax.h"

void saveScore(Dict save, Game game, int score) {
    // printf("in save\n");
    unsigned long id = hashf(game);
    insert(save, id, score);
    // printf("out save\n");
}

int loadScore(Dict save, Game game) {
    // printf("in load\n");
    int i;
    bool found;
    unsigned long id = hashf(game);
    i = search(save, id, &found);
    if (found) {
        return save[i]->score;
        // printf("out load\n");
    }
    // printf("out load\n");
    return 10000;
}

int minimax(Game game, int maxDepth) {
    int bestScore = -5000;
    int move = -1;
    int max = game->maxTurn - game->currentTurn;
    int col, row, score;
    Dict save = makeDict();
    for (int i = 0; i < game->width; i ++) {
        col = game->test[i];
        row = getRow(game, col);
        if (row == -1) continue;
        place(game, col, row);
        if (isPosAWin(game, col, row)) {
            undo(game, col, row); 
            freeDict(save);
            printf("%d, win\n", col);
            return col;
        }
        score = -negamax(game, maxDepth-1, -max, max, save);
        undo(game, col, row);
        printf("%d, %d, %d, %d\n", bestScore, move, score, col);
        if (score > bestScore) {
            bestScore = score;
            move = col;
        }
    }
    freeDict(save);
    printf("%d, %d\n", move, bestScore);
    return move;
}

int negamax(Game game, int maxDepth, int alpha, int beta, Dict save) {
    int load = loadScore(save, game);
    if (load != 10000) return load;
    if (maxDepth == 0) return 0;
    int max = game->maxTurn - game->currentTurn;
    if (beta > max) {
        beta = max;
        if (alpha >= beta) return beta;
    }
    int col, row, score;
    for (int i = 0; i < game->width; i ++) {
        col = game->test[i];
        row = getRow(game, col);
        if (row == -1) continue;
        place(game, col, row);
        if (isPosAWin(game, col, row)) {
            score = game->maxTurn - game->currentTurn;
            saveScore(save, game, score);
            undo(game, col, row);
            return score;
        }
        else score = -negamax(game, maxDepth - 1, -beta, -alpha, save);
        undo(game, col, row);
        if (score >= beta) {
            saveScore(save, game, score);
            return score;
        }
        if (score > alpha) alpha = score;
    }
    saveScore(save, game, alpha);
    return alpha;
}
