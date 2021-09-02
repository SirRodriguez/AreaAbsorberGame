#ifndef LINE_H
#define LINE_H

#include "../Shape.h"

class Line : public Shape {
protected:
	olc::Decal* lineDecal;
	int dx, dy;

public:
	Line(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy)
	: Shape(pge, ac, pos, _speed, _color), dx(_dx), dy(_dy), lineDecal(new olc::Decal(whiteLineSprite)){}

	virtual ~Line(){
		if(lineDecal != nullptr) delete lineDecal;
	}

	// Drawing ---
	virtual void draw() override {
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		float angle = - float(PI()) / 4.0f + std::atan(float(dy) / float(dx));
		olc::vf2d center = { float(whiteLineWidth / 2), float(whiteLineHeight / 2) };
		olc::vf2d scale = { float(whiteLineScaleToOneLength * getLength()), float(whiteLineScaleToOneLength * getLength()) };
		pixelGameEngine->DrawRotatedDecal(positionVector, lineDecal, angle, center, scale, color);
	}

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