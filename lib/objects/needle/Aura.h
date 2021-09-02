#ifndef AURA_H
#define AURA_H

#include "../../shapes/derivedShapes/Circle.h"

class Aura : public Circle{
protected:
	uint8_t alpha; // out of 100

public:
	Aura(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d pos, int _speed, const olc::Pixel& _color, int newRadius, uint8_t newAlpha)
	: Circle(pge, ac, pos, _speed, _color, newRadius), alpha(std::max(std::min(newAlpha, (uint8_t)100), (uint8_t)0)){}

	// Drawing ---
	virtual void draw() override {
		uint8_t c = 100 - alpha;
		uint8_t r = alpha * color.r / 100 + c * 255 / 100;
		uint8_t g = alpha * color.g / 100 + c * 255 / 100;
		uint8_t b = alpha * color.b / 100 + c * 255 / 100;
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		olc::vf2d offset = { (whiteCirclePixelWidth * whiteCircleScaleToOneRadius * radius) / 2, (whiteCirclePixelHeight * whiteCircleScaleToOneRadius * radius) / 2 };
		pixelGameEngine->DrawDecal(positionVector - offset, circleDecal, { whiteCircleScaleToOneRadius * radius, whiteCircleScaleToOneRadius * radius }, olc::Pixel(r, g, b));
	}

	virtual void move() override {
		// Will move with the needle
	}
};

#endif