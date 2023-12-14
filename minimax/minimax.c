#include "minimax.h"

#ifndef TEST_H
#define TEST_H
int TEST[] = {3, 2, 4, 1, 5, 0, 6};
#endif

int minimax(Game g, int maxDepth, Player p, Player other) {
    int bestScore = -5000;
    int move = -1;
    int col, row, score;
    for (int i=0; i < 7; i ++) {
        col = TEST[i];
        row = placeInCol(g, col, p);
        //printf("col %d, row %d\n", col, row);
        if (row == -1) continue;
        if (isPosAWin(g, col, row)) {
            undo(g, col, row); 
            return col;
        }
        score = minimaxMin(g, maxDepth-1, other, p, -1000, 1000);
        undo(g, col, row);
        printf("%d, %d, %d, %d\n", bestScore, move, score, col);
        if (score > bestScore) {
            bestScore = score;
            move = col;
        }
    }
    return move;
}

int minimaxMax(Game g, int maxDepth, Player p, Player other, int alpha, int beta) {
    //printf("%d\n", maxDepth);
    if (maxDepth == 0) return 0;
    int bestScore = -5000;
    int col, row, score;
    for (int i=0; i < 7; i ++) {
        col = TEST[i];
        row = placeInCol(g, col, p);
        if (row == -1) continue;
        if (isPosAWin(g, col, row)) score = 100;
        else score = minimaxMin(g, maxDepth-1, other, p, alpha, beta);
        undo(g, col, row);
        if (score > 0) score --;
        else if (score < 0) score ++;
        if (score > bestScore)
            bestScore = score;
        if (score > alpha)
            alpha = score;
        if (beta <= alpha) return bestScore;
    }
    return bestScore;
}

int minimaxMin(Game g, int maxDepth, Player p, Player other, int alpha, int beta) {
    //printf("%d\n", maxDepth);
    if (maxDepth == 0) return 0;
    int bestScore = 5000;
    int col, row, score;
    for (int i=0; i < 7; i ++) {
        col = TEST[i];
        row = placeInCol(g, col, p);
        if (row == -1) continue;
        if (isPosAWin(g, col, row)) score = -100;
        else score = minimaxMax(g, maxDepth-1, other, p, alpha, beta);
        undo(g, col, row);
        // if (score > 0) score --;
        // else if (score < 0) score ++;
        if (score < bestScore)
            bestScore = score;
        if (score < beta)
            beta = score;
        if (beta <= alpha) return bestScore;
    }
    return bestScore;
}
