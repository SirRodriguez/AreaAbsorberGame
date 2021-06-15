#ifndef BUDDYPOWERUP_H
#define BUDDYPOWERUP_H

#include "..\shapes\derivedShapes\Square.h"

class BuddyPowerUp: public Square{
public:
	BuddyPowerUp()
	: Square(){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Square(pge, pos, _speed, _color, newLength){}

	void move() override {
		// It moves down
		movePosition(olc::vi2d(0, speed));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif