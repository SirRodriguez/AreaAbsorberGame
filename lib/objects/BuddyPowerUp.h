#ifndef BUDDYPOWERUP_H
#define BUDDYPOWERUP_H

#include "../shapes/derivedShapes/Square.h"
#include "../Direction.h"

class BuddyPowerUp: public Square{
protected:
	Direction dir;

public:
	BuddyPowerUp()
	: Square(){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength, Direction directionCode)
	: Square(pge, pos, _speed, _color, newLength), dir(directionCode){}

	void move() override {
		switch(dir){
			case Direction::UP: moveUp(); break;
			case Direction::DOWN: moveDown(); break;
			case Direction::LEFT: moveLeft(); break;
			case Direction::RIGHT: moveRight(); break;
			case Direction::UPRIGHT: moveUpRight(); break;
			case Direction::UPLEFT: moveUpLeft(); break;
			case Direction::DOWNLEFT: moveDownLeft(); break;
			case Direction::DOWNRIGHT: moveDownRight(); break;
			default: break;
		}
	}

	bool outOfBounds() override {
		switch(dir){
			case Direction::UP: return !belowTopOfScreen();
			case Direction::DOWN: return !aboveBottomOfScreen();
			case Direction::LEFT: return !rightOfLeftOfScreen();
			case Direction::RIGHT: return !leftOfRightOfScreen();
			case Direction::UPRIGHT: return !belowTopOfScreen() || !leftOfRightOfScreen();
			case Direction::UPLEFT: return !belowTopOfScreen() || !rightOfLeftOfScreen();
			case Direction::DOWNLEFT: return !aboveBottomOfScreen() || !rightOfLeftOfScreen();
			case Direction::DOWNRIGHT: return !aboveBottomOfScreen() || !leftOfRightOfScreen();
			default: return !belowTopOfScreen() || !aboveBottomOfScreen() || !rightOfLeftOfScreen() || !leftOfRightOfScreen();
		}
	}
};

#endif