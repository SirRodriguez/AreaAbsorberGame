#ifndef AURA_H
#define AURA_H

#include "../../shapes/derivedShapes/Circle.h"

class Aura : public Circle{
protected:
	uint8_t alpha; // out of 100

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		if(colorToDraw == olc::WHITE){
			pixelGameEngine->FillCircle(position, radius, colorToDraw);
		}else{
			uint8_t c = 100 - alpha;
			uint8_t r = alpha * colorToDraw.r / 100 + c * 255 / 100;
			uint8_t g = alpha * colorToDraw.g / 100 + c * 255 / 100;
			uint8_t b = alpha * colorToDraw.b / 100 + c * 255 / 100;
			pixelGameEngine->FillCircle(position, radius, olc::Pixel(r, g, b));
		}
	}

public:
	Aura()
	: Circle(){}
	Aura(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d pos, int _speed, const olc::Pixel& _color, int newRadius, uint8_t newAlpha)
	: Circle(pge, ac, pos, _speed, _color, newRadius), alpha(std::max(std::min(newAlpha, (uint8_t)100), (uint8_t)0)){}

	virtual void move() override {
		// Will move with the needle
	}
};

#endif