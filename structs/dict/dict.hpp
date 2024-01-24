#include <iostream>
#include "../game/game.hpp"

using namespace std;

class Data {
    public:
        Data(unsigned long id, int score = 0);
        void operator=(int val);
        bool operator==(unsigned long other);
        bool operator!=(unsigned long other);
        string repr();
        int value();

    private:
        unsigned long id;
        int score;
};

class Dict {
    public:
        Dict(int size);
        ~Dict();
        Data& operator[](unsigned long id);
        string repr();
        int length();

    private:
        Data** arr;
        int size;
        int nb;

        int search(unsigned long id, bool *found);
};

unsigned long hashf(Game *game);
void dictTest();
