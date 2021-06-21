#ifndef CIRCLECAR_H
#define CIRCLECAR_H

#include "../shapes/derivedShapes/flower/Flower.h"

class CircleCar: public Flower{
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


	void movePedalsUp(){ movePedalsPosition(olc::vi2d(0, -speed)); }
	void movePedalsDown(){ movePedalsPosition(olc::vi2d(0, speed)); }
	void movePedalsLeft(){ movePedalsPosition(olc::vi2d(-speed, 0)); }
	void movePedalsRight(){ movePedalsPosition(olc::vi2d(speed, 0)); }
	void movePedalsUpLeft(){ movePedalsPosition(olc::vi2d(-speed, -speed)); }
	void movePedalsUpRight(){ movePedalsPosition(olc::vi2d(speed, -speed)); }
	void movePedalsDownLeft(){ movePedalsPosition(olc::vi2d(-speed, speed)); }
	void movePedalsDownRight(){ movePedalsPosition(olc::vi2d(speed, speed)); }

public:
	CircleCar()
	: Flower(){}
	CircleCar(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _pedalColor, int newRadius, int pedals, double degOffset, int directionCode)
	: Flower(pge, pos, _speed, _color, _pedalColor, newRadius, pedals, degOffset){
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

		moveAllPedals();
	}

	void moveAllPedals() override {
		switch(dir){
			case Direction::UP: movePedalsUp(); break;
			case Direction::DOWN: movePedalsDown(); break;
			case Direction::LEFT: movePedalsLeft(); break;
			case Direction::RIGHT: movePedalsRight(); break;
			case Direction::UPRIGHT: movePedalsUpRight(); break;
			case Direction::UPLEFT: movePedalsUpLeft(); break;
			case Direction::DOWNLEFT: movePedalsDownLeft(); break;
			case Direction::DOWNRIGHT: movePedalsDownRight(); break;
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