#ifndef SQUARE_H
#define SQUARE_H

#include "../Shape.h"

class Square: public Shape{
protected:
	int length;

public:
	Square(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Shape(pge, ac, pos, _speed, _color), length(newLength){}

	virtual void draw() override {
		pixelGameEngine->FillRectDecal(getTopLeftPoint(), olc::vi2d(length, length), color);
	}
	
	// Moving ---
	virtual void move() = 0;

	// Lengths ---
	void setLength(int l){ length = l; }
	void addLength(int l){ length += l; }
	int getLength(){ return length; }

	// Points ---
	olc::vi2d getTopLeftPoint(){ return position + olc::vi2d(-length / 2, -length / 2); }
	olc::vi2d getTopRightPoint(){ return position + olc::vi2d(length / 2, -length / 2); }
	olc::vi2d getBotLeftPoint(){ return position + olc::vi2d(-length / 2, length / 2); }
	olc::vi2d getBotRightPoint(){ return position + olc::vi2d(length / 2, length / 2); }
};

#endif