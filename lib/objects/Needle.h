#ifndef NEEDLE_H
#define NEEDLE_H

#include "..\shapes\derivedShapes\Line.h"

class Needle: public Line{
public:
	Needle()
	: Line(){}
	Needle(olc::PixelGameEngine& pge)
	: Line(pge){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Line(pge, pos){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Line(pge, pos, _speed){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Line(pge, pos, _speed, _color){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy)
	: Line(pge, pos, _speed, _color, _dx, _dy){}

	void move(int pixels){
		// Moves down
		movePosition(olc::vi2d(0, pixels));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif