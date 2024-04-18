#include "player.hpp"

using namespace std;

Player::Player(const char pion, const string& color)
    : pion{pion}, color{color}
{}

ostream& operator<<(ostream& os, const Player& p) {
    os << p.getColor() << p.getPion() << "\033[0m";
    return os;
}

bool operator==(const Player& p1, const Player& p2) {
    return p1.getPion() == p2.getPion();
}

bool operator!=(const Player& p1, const Player& p2) {
    return !operator==(p1, p2);
}


namespace std {
    size_t hash<Player>::operator()(const Player& p) const {
        return hash<char>()(p.getPion());
    }
}