#ifndef ANIMATIONLINE_H
#define ANIMATIONLINE_H

#include "../AnimationShape.h"

class AnimationLine: public AnimationShape{
protected:
	int dx, dy;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->DrawLine(getStartPoint(), getEndPoint(), colorToDraw);
	}

public:
	AnimationLine()
	: AnimationShape(), dx(0), dy(0){}
	AnimationLine(olc::PixelGameEngine& pge, olc::vi2d& pos, const olc::Pixel& _color, int _dx, int _dy)
	: AnimationShape(pge, pos, _color), dx(_dx), dy(_dy){}

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