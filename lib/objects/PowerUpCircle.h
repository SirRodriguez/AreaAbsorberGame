#ifndef POWERUPCIRCLE_H
#define POWERUPCIRCLE_H

#include "..\shapes\derivedShapes\Circle.h"

class PowerUpCircle: public Circle{
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
	PowerUpCircle()
	: Circle(){}
	PowerUpCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int directionCode)
	: Circle(pge, pos, _speed, _color, newRadius){
		switch(directionCode){
			case 0: // UP
				dir = Direction::UP;
				break;
			case 1: // DOWN
				dir = Direction::DOWN;
				break;
			case 2: // LEFT
				dir = Direction::LEFT;
				break;
			case 3: // RIGHT
				dir = Direction::RIGHT;
				break;
			case 4: // UPLEFT
				dir = Direction::UPLEFT;
				break;
			case 5: // UPRIGHT
				dir = Direction::UPRIGHT;
				break;
			case 6: // DOWNLEFT
				dir = Direction::DOWNLEFT;
				break;
			case 7: // DOWNRIGHT
				dir = Direction::DOWNRIGHT;
				break;
			default:
				dir = Direction::UP;
				break;
		}
	}

	// moving
	void move() override {
		switch(dir){
			case Direction::UP:
				movePosition(olc::vi2d(0, -speed));
				break;
			case Direction::DOWN:
				movePosition(olc::vi2d(0, speed));
				break;
			case Direction::LEFT:
				movePosition(olc::vi2d(-speed, 0));
				break;
			case Direction::RIGHT:
				movePosition(olc::vi2d(speed, 0));
				break;
			case Direction::UPRIGHT:
				movePosition(olc::vi2d(speed, -speed));
				break;
			case Direction::UPLEFT:
				movePosition(olc::vi2d(-speed, -speed));
				break;
			case Direction::DOWNLEFT:
				movePosition(olc::vi2d(-speed, speed));
				break;
			case Direction::DOWNRIGHT:
				movePosition(olc::vi2d(speed, speed));
				break;
			default:
				break;
		}
	}

	bool outOfBounds() override {
		switch(dir){
			case Direction::UP:
				return !belowTopOfScreen();
				
			case Direction::DOWN:
				return !aboveBottomOfScreen();
				
			case Direction::LEFT:
				return !rightOfLeftOfScreen();
				
			case Direction::RIGHT:
				return !leftOfRightOfScreen();
				
			case Direction::UPRIGHT:
				return !belowTopOfScreen() ||
					!leftOfRightOfScreen();
					
			case Direction::UPLEFT:
				return !belowTopOfScreen() ||
					!rightOfLeftOfScreen();
					
			case Direction::DOWNLEFT:
				return !aboveBottomOfScreen() ||
					!rightOfLeftOfScreen();
					
			case Direction::DOWNRIGHT:
				return !aboveBottomOfScreen() ||
					!leftOfRightOfScreen();
					
			default:
				return !belowTopOfScreen() ||
					!aboveBottomOfScreen() ||
					!rightOfLeftOfScreen() ||
					!leftOfRightOfScreen();
		}
	}
};

#endif