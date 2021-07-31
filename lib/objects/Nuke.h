#ifndef NUKE_H
#define NUKE_H

#include "../shapes/derivedShapes/flower/Flower.h"
#include "../Direction.h"

#define NUMPEDALS 7
#define PEDALANGLEOFFSET 0.0

class Nuke: public Flower{
protected:
	Direction dir;

public:
	Nuke()
	: Flower(){}
	Nuke(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _pedalColor, int newRadius, Direction directionCode)
	: Flower(pge, pos, _speed, _color, _pedalColor, newRadius, NUMPEDALS, PEDALANGLEOFFSET), dir(directionCode){}

	void move() override{
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

		fixPedalsToPosition();
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