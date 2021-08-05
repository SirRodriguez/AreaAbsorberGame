#ifndef ANIMATIONSHAPE_H
#define ANIMATIONSHAPE_H

class AnimationShape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	olc::Pixel color;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) = 0;

public:
	AnimationShape()
	: pixelGameEngine(nullptr), position(olc::vi2d(0,0)), color(olc::WHITE){}
	AnimationShape(olc::PixelGameEngine& pge, olc::vi2d& pos, const olc::Pixel& _color)
	: pixelGameEngine(&pge), position(pos), color(_color){}

	virtual ~AnimationShape(){}

	// Position
	virtual void setPosition(olc::vi2d point){ position = point; }
	virtual void movePosition(olc::vi2d otherPoint){ position += otherPoint; }
	virtual const olc::vi2d& getPosition(){ return position; }

	// Drawing
	virtual void draw(){ drawWithColor(color); }
	virtual void clear(){ drawWithColor(olc::WHITE); }
};

#endif