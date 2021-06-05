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
	PowerUpCircle(olc::PixelGameEngine& pge)
	: Circle(pge){}
	PowerUpCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos){}
	PowerUpCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius, int directionCode)
	: Circle(pge, pos, newRadius){
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
	void move(int pixels) override {
		switch(dir){
			case Direction::UP:
				movePosition(olc::vi2d(0, -pixels));
				break;
			case Direction::DOWN:
				movePosition(olc::vi2d(0, pixels));
				break;
			case Direction::LEFT:
				movePosition(olc::vi2d(-pixels, 0));
				break;
			case Direction::RIGHT:
				movePosition(olc::vi2d(pixels, 0));
				break;
			case Direction::UPRIGHT:
				movePosition(olc::vi2d(pixels, -pixels));
				break;
			case Direction::UPLEFT:
				movePosition(olc::vi2d(-pixels, -pixels));
				break;
			case Direction::DOWNLEFT:
				movePosition(olc::vi2d(-pixels, pixels));
				break;
			case Direction::DOWNRIGHT:
				movePosition(olc::vi2d(pixels, pixels));
				break;
			default:
				break;
		}
	}
};

#endif