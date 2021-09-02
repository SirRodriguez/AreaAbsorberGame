#ifndef NEEDLE_H
#define NEEDLE_H

#include "../../shapes/derivedShapes/Line.h"
#include "../../Direction.h"
#include "./Aura.h"

class Needle: public Line{
protected:
	Direction dir;
	Aura aura;

public:
	Needle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int _dx, int _dy, Direction directionCode)
	: Line(pge, ac, pos, _speed, _color, _dx, _dy), dir(directionCode), aura(Aura(pge, ac, pos, 0, olc::RED, getLength() / 2, 25)){}

	virtual ~Needle(){}

	// Drawing
	virtual void draw() override {
		// Draw the arua
		aura.draw();

		// Draw the Line
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		float angle = - float(PI()) / 4.0f + std::atan(float(dy) / float(dx));
		olc::vf2d center = { float(whiteLineWidth / 2), float(whiteLineHeight / 2) };
		olc::vf2d scale = { float(whiteLineScaleToOneLength * getLength()), float(whiteLineScaleToOneLength * getLength()) };
		pixelGameEngine->DrawRotatedDecal(positionVector, lineDecal, angle, center, scale, color);
	}

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
};

#endif