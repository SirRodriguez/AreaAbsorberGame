#ifndef CAR_H
#define CAR_H

#include "../../shapes/derivedShapes/flower/Flower.h"

#define NUMWHEELS 4
#define WHEELANGLEOFFSET 45.0

#define ACTIVATELIFE 100

class Car: public Flower{
protected:
	int life;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		if(isActive() || colorToDraw == olc::WHITE){
			pixelGameEngine->FillCircle(position, radius, colorToDraw);

			for(auto it = pedals.begin(); it != pedals.end(); ++it){
				if(colorToDraw == olc::WHITE){
					it->clear();
				}else{
					it->draw();
				}
			}
		}
	}

public:
	Car()
	: Flower(), life(0){}
	Car(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _wheelColor, int newRadius)
	: Flower(pge, ac, pos, _speed, _color, _wheelColor, newRadius, NUMWHEELS, WHEELANGLEOFFSET), life(0){}


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