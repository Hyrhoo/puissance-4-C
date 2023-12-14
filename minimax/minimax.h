#include "../structs/structs.h"

int minimax(Game g, int maxDepth, Player p, Player other);
int minimaxMax(Game g, int maxDepth, Player p, Player other, int alpha, int beta, List *save);
int minimaxMin(Game g, int maxDepth, Player p, Player other, int alpha, int beta, List *save);