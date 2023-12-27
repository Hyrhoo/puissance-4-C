#include "../structs/dict/dict.h"

int minimax(Game g, int maxDepth);
int minimaxMax(Game g, int maxDepth, int alpha, int beta, Dict save);
int minimaxMin(Game g, int maxDepth, int alpha, int beta, Dict save);