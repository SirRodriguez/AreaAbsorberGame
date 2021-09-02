#ifndef BOX_H
#define BOX_H

#include "Square.h"

class Box: public Square{
protected:
	olc::Decal* boxDecal;
public:
	Box(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Square(pge, ac, pos, _speed, _color, newLength), boxDecal(new olc::Decal(whiteSquareOutlineSprite)){}

	~Box(){
		if(boxDecal != nullptr) delete boxDecal;
	}

	// Drawing ---
	virtual void draw() override{
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		olc::vf2d offset = { (whiteSquareOutlineWidth * whiteSquareOutlineScaleToOneLength * length / 2), (whiteSquareOutlineHeight * whiteSquareOutlineScaleToOneLength * length / 2) };
		olc::vf2d scale = { whiteSquareOutlineScaleToOneLength * length, whiteSquareOutlineScaleToOneLength * length };
		pixelGameEngine->DrawDecal(positionVector - offset, boxDecal, scale, color);
	}

	// Moving ---
	virtual void move() = 0;
};

#endif