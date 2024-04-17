#include <iostream>
#include "player.hpp"

using namespace std;

int main() {
    Player p1 = {'X', "\033[0;36m"};
    cout << p1 << endl;
    return 0;
}