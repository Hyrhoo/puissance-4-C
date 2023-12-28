#include "../structs/dict/dict.h"

int minimax(Game g, int maxDepth);
int negamax(Game game, int maxDepth, int alpha, int beta, Dict save);