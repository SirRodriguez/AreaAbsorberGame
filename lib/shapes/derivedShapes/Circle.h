#ifndef CIRCLE_H
#define CIRCLE_H

#include "..\Shape.h"

#define PI (355 / 113)
#define RECPI (113 / 355)
class Circle : public Shape{
protected:
	int radius;

	virtual void draw(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillCircle(position, radius, colorToDraw);
	}

public:
	Circle()
	: Shape(), radius(0){}
	Circle(olc::PixelGameEngine& pge)
	: Shape(pge), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Shape(pge, pos, _speed), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Shape(pge, pos, _speed, _color), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Shape(pge, pos, _speed, _color), radius(newRadius){}

	virtual void draw(){
		draw(color);
	}

	// Size ---
	void setRadius(int r){ radius = r; }
	void addRadius(int r){ radius += r; }
	int getRadius(){ return radius; }

	// Moving
	virtual void move(int pixels) = 0;

	~Circle(){}
};

#endif