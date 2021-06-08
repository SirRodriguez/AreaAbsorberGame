#ifndef TRAP_H
#define TRAP_H

#include "..\shapes\derivedShapes\Box.h"

class Trap: public Box{
public:
	Trap()
	: Box(){}
	Trap(olc::PixelGameEngine& pge)
	: Box(pge){}
	Trap(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Box(pge, pos){}
	Trap(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Box(pge, pos, _speed){}
	Trap(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Box(pge, pos, _speed, _color){}
	Trap(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Box(pge, pos, _speed, _color, newLength){}

	void move(int pixels){
		// Moves down
		movePosition(olc::vi2d(0, pixels));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif