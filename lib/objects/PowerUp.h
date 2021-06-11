#ifndef POWERUP_H
#define POWERUP_H

#include "..\shapes\derivedShapes\Triangle.h"

class PowerUp: public Triangle{

public:
	PowerUp()
	: Triangle(){}
	PowerUp(olc::PixelGameEngine& pge)
	: Triangle(pge){}
	PowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Triangle(pge, pos){}
	PowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Triangle(pge, pos, _speed){}
	PowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Triangle(pge, pos, _speed, _color){}
	PowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newHeight)
	: Triangle(pge, pos, _speed, _color, newHeight){}

	void move() override {
		// Moves down
		movePosition(olc::vi2d(0, speed));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}

};

#endif