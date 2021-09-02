#ifndef CIRCLE_H
#define CIRCLE_H

#include "../Shape.h"

class Circle : public Shape{
protected:
	olc::Decal* circleDecal;
	int radius;

public:
	Circle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Shape(pge, ac, pos, _speed, _color), radius(newRadius), circleDecal(new olc::Decal(whiteCircleSprite)){}

	virtual ~Circle(){
		if(circleDecal != nullptr) delete circleDecal;
	}

	// Drawing ---
	virtual void draw() override {
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		olc::vf2d offset = { (whiteCirclePixelWidth * whiteCircleScaleToOneRadius * radius) / 2, (whiteCirclePixelHeight * whiteCircleScaleToOneRadius * radius) / 2 };
		pixelGameEngine->DrawDecal(positionVector - offset, circleDecal, { whiteCircleScaleToOneRadius * radius, whiteCircleScaleToOneRadius * radius }, color);
	}

	// Size ---
	virtual void setRadius(int r){ radius = r; }
	virtual void addRadius(int r){ radius += r; }
	virtual int getRadius(){ return radius; }

	// Moving
	virtual void move() = 0;
};

#endif