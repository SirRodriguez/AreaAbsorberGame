#ifndef CIRCLE
#define CIRCLE

#include "..\Shape.h"

#define PI (355 / 113)
#define RECPI (113 / 355)
class Circle : public Shape{

	int radius;

public:
	Circle()
	: Shape(){}
	Circle(olc::PixelGameEngine& pge)
	: Shape(pge){}

	void draw(const olc::Pixel& color){
		pixelGameEngine->FillCircle(position, radius, color);
	}
	void clear(){
		pixelGameEngine->FillCircle(position, radius, olc::WHITE);
	}

	void setRadius(int r){ radius = r; }
	void addRadius(int r){ radius += r; }
	int getRadius(){ return radius; }
};

#endif