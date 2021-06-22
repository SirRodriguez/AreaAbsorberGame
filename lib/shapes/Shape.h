#ifndef SHAPE_H
#define SHAPE_H

class Shape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	int speed;
	olc::Pixel color;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) = 0;

public:
	Shape()
	: pixelGameEngine(nullptr), position(olc::vi2d(0,0)), speed(0), color(olc::WHITE){}
	Shape(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: pixelGameEngine(&pge), position(pos), speed(_speed), color(_color){}

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
	virtual void draw(){ drawWithColor(color); }
	virtual void clear(){ drawWithColor(olc::WHITE); }

	// Moving
	virtual void move() = 0;

	virtual ~Shape(){}
};

#endif