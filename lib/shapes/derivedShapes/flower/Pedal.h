#ifndef PEDAL_H
#define PEDAL_H

#include "../Circle.h"

class Pedal: public Circle{
public:
	Pedal(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Circle(pge, ac, pos, _speed, _color, newRadius){}

	virtual void move() override {
		// Do nothing
	}
};

#endif