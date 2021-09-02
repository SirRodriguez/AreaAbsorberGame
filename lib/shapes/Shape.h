#ifndef SHAPE_H
#define SHAPE_H

#include "../containers/AnimationContainer.h"

class Shape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	AnimationContainer* animationContainer;
	olc::vi2d position;
	int speed;
	olc::Pixel color;

	virtual void moveUp(){ movePosition(olc::vi2d(0, -speed)); }
	virtual void moveDown(){ movePosition(olc::vi2d(0, speed)); }
	virtual void moveLeft(){ movePosition(olc::vi2d(-speed, 0)); }
	virtual void moveRight(){ movePosition(olc::vi2d(speed, 0)); }
	virtual void moveUpLeft(){ movePosition(olc::vi2d(-speed, -speed)); }
	virtual void moveUpRight(){ movePosition(olc::vi2d(speed, -speed)); }
	virtual void moveDownLeft(){ movePosition(olc::vi2d(-speed, speed)); }
	virtual void moveDownRight(){ movePosition(olc::vi2d(speed, speed)); }

public:
	Shape(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: pixelGameEngine(&pge), animationContainer(&ac), position(pos), speed(_speed), color(_color){}

	virtual ~Shape(){}

	// PI
	double PI(){ return 355.0 / 113.0; }
	double RECPI(){ return 113.0 / 335.0; }

	// Out of bounds
	virtual bool belowTopOfScreen(){ return position.y > 0; }
	virtual bool aboveBottomOfScreen(){	return position.y < pixelGameEngine->ScreenHeight(); }
	virtual bool rightOfLeftOfScreen(){	return position.x > 0; }
	virtual bool leftOfRightOfScreen(){	return position.x < pixelGameEngine->ScreenWidth();	}
	virtual bool outOfBounds(){
		return !belowTopOfScreen() ||
			!aboveBottomOfScreen() ||
			!rightOfLeftOfScreen() ||
			!leftOfRightOfScreen();
	}

	// Position
	virtual void setPosition(olc::vi2d point){ position = point; }
	virtual void movePosition(olc::vi2d otherPoint){ position += otherPoint; }
	virtual const olc::vi2d& getPosition(){ return position; }

	// Drawing
	virtual void draw() = 0;

	// Moving
	virtual void move() = 0;
	void moveToCord(int x, int y, int pixels){
		movePosition(olc::vi2d( x < position.x ? -pixels : pixels, y < position.y ? -pixels : pixels ));
	}
	void moveToPos(const olc::vi2d& pos, int pixels){
		moveToCord(pos.x, pos.y, pixels);
	}
};

#endif