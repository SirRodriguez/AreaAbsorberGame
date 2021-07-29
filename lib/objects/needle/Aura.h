#ifndef AURA_H
#define AURA_H

#include "../../shapes/derivedShapes/Circle.h"

class Aura : public Circle{
protected:
	uint8_t alpha;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->SetPixelMode(olc::Pixel::ALPHA);
		pixelGameEngine->FillCircle(position, radius, olc::Pixel(colorToDraw.r, colorToDraw.g, colorToDraw.b,  colorToDraw == olc::WHITE ? 255 : alpha));
		pixelGameEngine->SetPixelMode(olc::Pixel::NORMAL);
	}

public:
	Aura()
	: Circle(){}
	Aura(olc::PixelGameEngine& pge, olc::vi2d pos, int _speed, const olc::Pixel& _color, int newRadius, uint8_t newAlpha)
	: Circle(pge, pos, _speed, _color, newRadius), alpha(newAlpha){}

	virtual void move() override {
		// Will move with the needle
	}
};

#endif