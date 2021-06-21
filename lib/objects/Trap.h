#ifndef TRAP_H
#define TRAP_H

#include "../shapes/derivedShapes/Box.h"

class Trap: public Box{
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

	void moveUp(){ movePosition(olc::vi2d(0, -speed)); }
	void moveDown(){ movePosition(olc::vi2d(0, speed)); }
	void moveLeft(){ movePosition(olc::vi2d(-speed, 0)); }
	void moveRight(){ movePosition(olc::vi2d(speed, 0)); }
	void moveUpLeft(){ movePosition(olc::vi2d(-speed, -speed)); }
	void moveUpRight(){ movePosition(olc::vi2d(speed, -speed)); }
	void moveDownLeft(){ movePosition(olc::vi2d(-speed, speed)); }
	void moveDownRight(){ movePosition(olc::vi2d(speed, speed)); }

public:
	Trap()
	: Box(){}
	Trap(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength, int directionCode)
	: Box(pge, pos, _speed, _color, newLength){
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

	uint8_t getDirectionCode(){
		switch(dir){
			case Direction::UP: return 0;
			case Direction::DOWN: return 1;
			case Direction::LEFT: return 2;
			case Direction::RIGHT: return 3;
			case Direction::UPRIGHT: return 5;
			case Direction::UPLEFT: return 4;
			case Direction::DOWNLEFT: return 6;
			case Direction::DOWNRIGHT: return 7;
			default: return 1;
		}
	}
};

#endif