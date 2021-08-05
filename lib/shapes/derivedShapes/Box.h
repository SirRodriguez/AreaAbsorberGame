#ifndef BOX_H
#define BOX_H

#include "Square.h"

class Box: public Square{
protected:
	virtual void drawWithColor(const olc::Pixel& colorToDraw) override{
		pixelGameEngine->DrawRect(getTopLeftPoint(), olc::vi2d(length, length), colorToDraw);
	}

public:
	Box()
	: Square(){}
	Box(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Square(pge, ac, pos, _speed, _color, newLength){}

	// Moving ---
	virtual void move() = 0;
};

#endif