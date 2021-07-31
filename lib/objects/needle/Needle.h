#ifndef NEEDLE_H
#define NEEDLE_H

#include "../../shapes/derivedShapes/Line.h"
#include "../../Direction.h"
#include "./Aura.h"

class Needle: public Line{
protected:
	Direction dir;
	Aura aura;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		aura.draw();
		pixelGameEngine->DrawLine(getStartPoint(), getEndPoint(), colorToDraw);
	}

public:
	Needle()
	: Line(){}
	Needle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy, Direction directionCode)
	: Line(pge, pos, _speed, _color, _dx, _dy), dir(directionCode), aura(Aura(pge, pos, 0, olc::RED, getLength() / 2, 25)){}

	void move(){
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

		aura.setPosition(getPosition());
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

	virtual void clear() override {
		drawWithColor(olc::WHITE);
		aura.clear();
	}
};

#endif