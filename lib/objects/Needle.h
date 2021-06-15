#ifndef NEEDLE_H
#define NEEDLE_H

#include "..\shapes\derivedShapes\Line.h"

class Needle: public Line{
public:
	Needle()
	: Line(){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy)
	: Line(pge, pos, _speed, _color, _dx, _dy){}

	void move(){
		// Moves down
		movePosition(olc::vi2d(0, speed));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif