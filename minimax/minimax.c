#include "minimax.h"

#ifndef TEST_H
#define TEST_H
int TEST[] = {3, 2, 4, 1, 5, 0, 6};
#endif

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
    int col, row, score;
    Dict save = makeDict();
    for (col = 0; col < game->width; col ++) {
        // col = TEST[i];
        row = getRow(game, col);
        if (row == -1) continue;
        place(game, col, row);
        if (isPosAWin(game, col, row)) {
            undo(game, col, row); 
            freeDict(save);
            return col;
        }
        score = minimaxMin(game, maxDepth-1, -1000, 1000, save);
        undo(game, col, row);
        printf("%d, %d, %d, %d\n", bestScore, move, score, col);
        if (score > bestScore) {
            bestScore = score;
            move = col;
        }
        if (score == bestScore) {
            int mid = (game->width) / 2;
            if (abs(col - mid) < abs(move - mid))
                move = col;
        }
    }
    freeDict(save);
    return move;
}

int minimaxMax(Game game, int maxDepth, int alpha, int beta, Dict save) {
    // printf("in max\n");
    int load = loadScore(save, game);
    if (load != 10000) {
        // printf("out max\n");
        return load;
    }
    if (maxDepth == 0) return 0;
    int bestScore = -5000;
    int col, row, score;
    for (col = 0; col < game->width; col ++) {
        // col = TEST[i];
        row = getRow(game, col);
        // printf("\tmax %d %d\n", col, row);
        if (row == -1) continue;
        place(game, col, row);
        if (isPosAWin(game, col, row)) score = 100;
        else score = minimaxMin(game, maxDepth-1, alpha, beta, save);
        undo(game, col, row);
        (score > 0) ? score -- : (score < 0) ? score ++ : score;
        if (score > bestScore)
            bestScore = score;
        if (score > alpha)
            alpha = score;
        if (beta <= alpha) {
            saveScore(save, game, bestScore);
            // printf("out max\n");
            return bestScore;
        }
    }
    saveScore(save, game, bestScore);
    // printf("out max\n");
    return bestScore;
}

int minimaxMin(Game game, int maxDepth, int alpha, int beta, Dict save) {
    // printf("in min\n");
    int load = loadScore(save, game);
    if (load != 10000) {
        // printf("out min\n");
        return load;
    }
    if (maxDepth == 0) return 0;
    int bestScore = 5000;
    int col, row, score;
    for (int col = 0; col < game->width; col ++) {
        // col = TEST[i];
        row = getRow(game, col);
        // printf("\tmin %d %d\n", col, row);
        if (row == -1) continue;
        place(game, col, row);
        if (isPosAWin(game, col, row)) score = -100;
        else score = minimaxMax(game, maxDepth-1, alpha, beta, save);
        undo(game, col, row);
        (score > 0) ? score -- : (score < 0) ? score ++ : score;
        if (score < bestScore)
            bestScore = score;
        if (score < beta)
            beta = score;
        if (beta <= alpha) {
            saveScore(save, game, bestScore);
            // printf("out min\n");
            return bestScore;
        }
    }
    saveScore(save, game, bestScore);
    // printf("out min\n");
    return bestScore;
}
