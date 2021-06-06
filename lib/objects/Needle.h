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
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _dx, int _dy)
	: Line(pge, pos, _dx, _dy){}

	void move(int pixels){
		movePosition(olc::vi2d(0, pixels));
	}
};

#endif