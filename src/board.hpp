#ifndef BOARD_HPP
#define BOARD_HPP

#include "player.hpp"

class Board {
private:
	int hauteur;
	int largeur;
	

public:
	Board(int hauteur = 5, int largeur = 7);
};
#endif // BOARD_HPP
