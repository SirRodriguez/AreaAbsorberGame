#ifndef CIRCLE
#define CIRCLE

#include "..\Shape.h"

#define PI (355 / 113)
#define RECPI (113 / 355)
class Circle : public Shape{

	int radius;

public:
	Circle()
	: Shape(), radius(0){}
	Circle(olc::PixelGameEngine& pge)
	: Shape(pge), radius(0){}
	Circle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius)
	: Shape(pge, pos), radius(newRadius) {}

	void draw(const olc::Pixel& color){
		pixelGameEngine->FillCircle(position, radius, color);
	}
	void clear(){
		pixelGameEngine->FillCircle(position, radius, olc::WHITE);
	}

	void setRadius(int r){ radius = r; }
	void addRadius(int r){ radius += r; }
	int getRadius(){ return radius; }

	~Circle(){}
};

#endif