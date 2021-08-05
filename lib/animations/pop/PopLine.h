#ifndef POPLINE_H
#define POPLINE_H

#include "../../Direction.h"
#include "../shapes/AnimationLine.h"

class PopLine: public AnimationLine{
public:
	PopLine()
	: AnimationLine(){}
	PopLine(olc::PixelGameEngine& pge, olc::vi2d& pos, const olc::Pixel& _color, int _dx, int _dy)
	: AnimationLine(pge, pos, 0, _color, _dx, _dy), dir(directionCode){}

	virtual void move() override {
		// Do Nothing
	}
};

#endif