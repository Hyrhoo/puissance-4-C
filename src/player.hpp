#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>

class Player {
private:
	char pion;
	std::string color;

public:
	Player(const char pion, const std::string& color);
	char getPion() const {return pion;}
	std::string getColor() const {return color;}
};

std::ostream& operator<<(std::ostream& os, const Player& p);

#endif // PLAYER_HPP
