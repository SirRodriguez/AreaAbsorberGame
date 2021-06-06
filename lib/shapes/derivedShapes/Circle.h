#ifndef CIRCLE_H
#define CIRCLE_H

#include "..\Shape.h"

#define PI (355 / 113)
#define RECPI (113 / 355)
class Circle : public Shape{
protected:
	int radius;

public:
	Circle()
	: Shape(), radius(0){}
	Circle(olc::PixelGameEngine& pge)
	: Shape(pge), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius)
	: Shape(pge, pos), radius(newRadius){}

	// Drawing ---
	void draw(const olc::Pixel& color){
		pixelGameEngine->FillCircle(position, radius, color);
	}
	void clear(){
		draw(olc::WHITE);
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