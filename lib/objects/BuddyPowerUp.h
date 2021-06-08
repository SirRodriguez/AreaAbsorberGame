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
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Square(pge, pos, _speed){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Square(pge, pos, _speed, _color){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Square(pge, pos, _speed, _color, newLength){}

	void move(int pixels){
		// It moves down
		movePosition(olc::vi2d(0, pixels));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif