#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Shape.h"

#define SQRT3 97 / 56
#define RECSQRT3 56 / 97
class Triangle : public Shape{
protected:
	int height;

	// Drawing ---
	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillTriangle(topPoint(), botLeftPoint(), botRightPoint(), colorToDraw);
	}

public:
	Triangle()
	: Shape(), height(0){}
	Triangle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newHeight)
	: Shape(pge, ac, pos, _speed, _color), height(newHeight){}
	
	// Moving ---
	virtual void move() = 0;

	// Height ---
	void setHeight(int h){ height = h; }
	void addHeight(int h){ height += h; }
	int getHeight(){ return height; }

	// Points ---
	olc::vi2d topPoint(){ return position + olc::vi2d(0, -(height * 2) / 3); }
	olc::vi2d botLeftPoint(){ return position + olc::vi2d(-height * RECSQRT3, height / 3); }
	olc::vi2d botRightPoint(){ return position + olc::vi2d(height * RECSQRT3, height / 3); }
};

#endif