#include <iostream>
#include <unordered_set>
#include "player.hpp"

using namespace std;

int main() {
    Player p1 = {'X', "\033[0;36m"};
    Player p2 = {'0', "\033[0;31m"};
    unordered_set<Player> m{p1, p2};
    cout << p1 << p2 << endl;
    cout << hash<Player>()(p1) << endl;
    cout << hash<Player>()(p2) << endl;
    cout << (p1 == p2) << endl;
    cout << (p1 != p2) << endl;
    for (Player p : m) {
        cout << p << " ";
    }
    cout << endl;
    return 0;
}