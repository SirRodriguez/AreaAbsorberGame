#ifndef SHAPE_H
#define SHAPE_H

class Shape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	int speed;
	olc::Pixel color;

	virtual void draw(const olc::Pixel& colorToDraw) = 0;

public:
	Shape()
	: pixelGameEngine(nullptr), position(olc::vi2d(0,0)), speed(0), color(olc::WHITE){}
	Shape(olc::PixelGameEngine& pge)
	: pixelGameEngine(&pge), position(olc::vi2d(0,0)), speed(0), color(olc::WHITE){}
	Shape(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: pixelGameEngine(&pge), position(pos), speed(0), color(olc::WHITE){}
	Shape(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: pixelGameEngine(&pge), position(pos), speed(_speed), color(olc::WHITE){}
	Shape(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: pixelGameEngine(&pge), position(pos), speed(_speed), color(_color){}

	bool belowTopOfScreen(){ return position.y > 0; }
	bool aboveBottomOfScreen(){	return position.y < pixelGameEngine->ScreenHeight(); }
	bool rightOfLeftOfScreen(){	return position.x > 0; }
	bool leftOfRightOfScreen(){	return position.x < pixelGameEngine->ScreenWidth();	}
	virtual bool outOfBounds(){
		return !belowTopOfScreen() ||
			!aboveBottomOfScreen() ||
			!rightOfLeftOfScreen() ||
			!leftOfRightOfScreen();
	}

	void setPosition(olc::vi2d point){ position = point; }
	void movePosition(olc::vi2d otherPoint){ position += otherPoint; }
	const olc::vi2d& getPosition(){ return position; }

	virtual void draw() = 0;
	void clear(){ draw(olc::WHITE); }

	virtual void move(int pixels) = 0;

	virtual ~Shape(){}
};

#endif