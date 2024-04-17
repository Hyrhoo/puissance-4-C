#include "player.hpp"

using namespace std;

Player::Player(const char pion, const string& color)
    : pion{pion}, color{color}
{}

ostream& operator<<(ostream& os, const Player& p) {
    os << p.getColor() << p.getPion() << "\033[0m";
    return os;
}