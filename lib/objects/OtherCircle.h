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
	OtherCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Circle(pge, pos, _speed){}
	OtherCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Circle(pge, pos, _speed, _color){}
	OtherCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Circle(pge, pos, _speed, _color, newRadius){}

	void move(int pixels){
		// Moves down
		movePosition(olc::vi2d(0, pixels));
	}

	bool outOfBounds() override {
		return !aboveBottomOfScreen();
	}
};

#endif