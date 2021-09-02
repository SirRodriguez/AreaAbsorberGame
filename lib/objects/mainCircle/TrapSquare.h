#ifndef TRAPSQUARE_H
#define TRAPSQUARE_H

#include "../../shapes/derivedShapes/Box.h"

#define MAXLIFETIME 60

class TrapSquare: public Box{
protected:
	uint8_t lifeTimeInFrames;

public:
	TrapSquare(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Box(pge, ac, pos, _speed, _color, newLength), lifeTimeInFrames(0){}

	virtual ~TrapSquare(){}

	// Drawing ---
	virtual void draw() override {
		if(isActive()){
			olc::vf2d positionVector = { float(position.x), float(position.y) };
			olc::vf2d offset = { (whiteSquareOutlineWidth * whiteSquareOutlineScaleToOneLength * length / 2), (whiteSquareOutlineHeight * whiteSquareOutlineScaleToOneLength * length / 2) };
			olc::vf2d scale = { whiteSquareOutlineScaleToOneLength * length, whiteSquareOutlineScaleToOneLength * length };
			pixelGameEngine->DrawDecal(positionVector - offset, boxDecal, scale, color);
		}
	}

	// Moving  ---
	void move(){
		// This is used to count down the life of the square
		if(lifeTimeInFrames > 0){
			lifeTimeInFrames--;
		}
	}

	// Activity
	void activate(){ lifeTimeInFrames = MAXLIFETIME; }
	void inactivate(){ lifeTimeInFrames = 0; }

	bool isActive(){ return lifeTimeInFrames > 0; }
	bool isNotActive(){ return !isActive(); }
};

#endif