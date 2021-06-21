#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Shape.h"

class Circle : public Shape{
protected:
	int radius;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillCircle(position, radius, colorToDraw);
	}

public:
	Circle()
	: Shape(), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Shape(pge, pos, _speed, _color), radius(newRadius){}

	// PI
	double PI(){ return 355.0 / 113.0; }
	double RECPI(){ return 113.0 / 335.0; }

	// Size ---
	void setRadius(int r){ radius = r; }
	void addRadius(int r){ radius += r; }
	int getRadius(){ return radius; }

	// Moving
	virtual void move() = 0;

	~Circle(){}
};

#endif