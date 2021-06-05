#ifndef BUDDYPOWERUP_H
#define BUDDYPOWERUP_H

#include "..\shapes\derivedShapes\Square.h"

class BuddyPowerUp: public Square{
public:
	BuddyPowerUp()
	: Square(){}
	BuddyPowerUp(olc::PixelGameEngine& pge)
	: Square(pge){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Square(pge, pos){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int newLength)
	: Square(pge, pos){}
};

#endif