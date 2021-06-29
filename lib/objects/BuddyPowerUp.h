#ifndef BUDDYPOWERUP_H
#define BUDDYPOWERUP_H

#include "../shapes/derivedShapes/Square.h"

class BuddyPowerUp: public Square{
private:
	enum Direction{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UPLEFT,
		UPRIGHT,
		DOWNLEFT,
		DOWNRIGHT
	};

protected:
	Direction dir;

public:
	BuddyPowerUp()
	: Square(){}
	BuddyPowerUp(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength, int directionCode)
	: Square(pge, pos, _speed, _color, newLength){
		switch(directionCode){
			case 0: dir = Direction::UP; break;
			case 1: dir = Direction::DOWN; break;
			case 2: dir = Direction::LEFT; break;
			case 3: dir = Direction::RIGHT; break;
			case 4: dir = Direction::UPLEFT; break;
			case 5: dir = Direction::UPRIGHT; break;
			case 6: dir = Direction::DOWNLEFT; break;
			case 7: dir = Direction::DOWNRIGHT; break;
			default: dir = Direction::UP; break;
		}
	}

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