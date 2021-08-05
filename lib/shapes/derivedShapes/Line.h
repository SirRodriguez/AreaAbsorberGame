#ifndef LINE_H
#define LINE_H

#include "../Shape.h"

class Line : public Shape {
protected:
	int dx, dy;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->DrawLine(getStartPoint(), getEndPoint(), colorToDraw);
	}

public:
	Line()
	: Shape(), dx(0), dy(0){}
	Line(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy)
	: Shape(pge, ac, pos, _speed, _color), dx(_dx), dy(_dy){}

	// Moving ---
	virtual void move() = 0;

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
	int getLength(){ return  2 * (int)std::sqrt(dx*dx+dy*dy); }

};

#endif