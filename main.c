#include "structs/structs.h"

int main() {
    Game g = makeGame();
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 0, 'x');
    displayGame(g);
    placeInCol(g, 8, 'x');
    displayGame(g);
    return 0;
}