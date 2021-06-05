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
	PowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int newHeight)
	: Triangle(pge, pos, newHeight){}

};

#endif