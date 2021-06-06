#ifndef LINE_H
#define LINE_H

#include "..\Shape.h"

class Line : public Shape {
protected:
	int dx, dy;

public:
	Line()
	: Shape(), dx(0), dy(0){}
	Line(olc::PixelGameEngine& pge)
	: Shape(pge), dx(0), dy(0){}
	Line(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), dx(0), dy(0){}
	Line(olc::PixelGameEngine& pge, olc::vi2d& pos, int _dx, int _dy)
	: Shape(pge, pos), dx(_dx), dy(_dy){}

	// Drawing ---
	virtual void draw(const olc::Pixel& color){
		pixelGameEngine->DrawLine(getStartPoint(), getEndPoint(), color);
	}
	virtual void clear(){
		draw(olc::WHITE);
	}

	// Moving ---
	virtual void move(int pixels) = 0;

	// Setting values ---
	void setdx(int x){ dx = x; }
	void adddx(int x){ dx += x; }
	int getdx(){ return dx; }

	void setdy(int y){ dy = y; }
	void adddy(int y){ dy += y; }
	int getdy(){ return dy; }

	// Getters ---
	olc::vi2d getStartPoint(){ return position + olc::vi2d(-dx, -dy); }
	olc::vi2d getEndPoint(){ return position + olc::vi2d(dx, dy); }

};

#endif