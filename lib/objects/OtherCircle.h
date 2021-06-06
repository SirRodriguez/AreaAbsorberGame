#ifndef OTHERCIRCLE_H
#define OTHERCIRCLE_H

#include "..\shapes\derivedShapes\Circle.h"

class OtherCircle: public Circle{

public:
	OtherCircle()
	: Circle(){}
	OtherCircle(olc::PixelGameEngine& pge)
	: Circle(pge){}
	OtherCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos){}
	OtherCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius)
	: Circle(pge, pos, newRadius){}
};

#endif