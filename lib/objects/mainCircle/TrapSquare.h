#ifndef TRAPSQUARE_H
#define TRAPSQUARE_H

#include "../../shapes/derivedShapes/Box.h"

#define MAXLIFETIME 60

class TrapSquare: public Box{
protected:
	uint8_t lifeTimeInFrames;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		if(isActive() || colorToDraw == olc::WHITE){
			pixelGameEngine->DrawRect(getTopLeftPoint(), olc::vi2d(length, length), colorToDraw);
		}
	}

public:
	TrapSquare()
	: Box(), lifeTimeInFrames(0){}
	TrapSquare(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Box(pge, ac, pos, _speed, _color, newLength), lifeTimeInFrames(0){}

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