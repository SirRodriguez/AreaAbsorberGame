#ifndef CAR_H
#define CAR_H

#include "../../shapes/derivedShapes/flower/Flower.h"

#define NUMWHEELS 4
#define WHEELANGLEOFFSET 45.0

#define ACTIVATELIFE 100

class Car: public Flower{
protected:
	int life;

public:
	Car(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _wheelColor, int newRadius)
	: Flower(pge, ac, pos, _speed, _color, _wheelColor, newRadius, NUMWHEELS, WHEELANGLEOFFSET), life(0){}

	// Drawing ---
	virtual void draw() override {
		if(isActive()){
			// Draw the inner circle
			olc::vf2d positionVector = { float(position.x), float(position.y) };
			olc::vf2d offset = { (whiteCirclePixelWidth * whiteCircleScaleToOneRadius * radius) / 2, (whiteCirclePixelHeight * whiteCircleScaleToOneRadius * radius) / 2 };
			pixelGameEngine->DrawDecal(positionVector - offset, circleDecal, { whiteCircleScaleToOneRadius * radius, whiteCircleScaleToOneRadius * radius }, color);

			// Draw the wheels
			for(auto it = pedals.begin(); it != pedals.end(); ++it)
				(*it)->draw();
		}
	}

	// Moving  ---
	void move() override {
		fixPedalsToPosition();
	}

	// Activity
	void activate(){ life += ACTIVATELIFE; }
	void inactivate(){ life = 0; }

	bool isActive(){ return life > 0; }
	bool isNotActive(){ return !isActive(); }

	// Life
	void loseLife(int amount){ 
		life -= amount; 
		if(life < 0) life = 0;
	}
	int getLife(){ return life; }
};

#endif