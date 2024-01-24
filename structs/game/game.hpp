#include <iostream>

class Board {
    public:

    private:
        int height;
        int width;
        int **board;
        int *colHeight;
};

class Game {
    public:
        int height();
        int width();
        int select(int x, int y);

    private:
        Board board;
        int currentTurn;
        int maxTurn;
        int currentPlayer;
        int *testOrder;
        //PlayerPtr players[3];
        string plays;
} *GamePtr;
