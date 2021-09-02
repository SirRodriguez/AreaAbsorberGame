#ifndef ANIMATIONSHAPE_H
#define ANIMATIONSHAPE_H

class AnimationShape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	olc::Pixel color;

public:
	AnimationShape(olc::PixelGameEngine& pge, olc::vi2d& pos, const olc::Pixel& _color)
	: pixelGameEngine(&pge), position(pos), color(_color){}

	virtual ~AnimationShape(){}

	// PI
	double PI(){ return 355.0 / 113.0; }
	double RECPI(){ return 113.0 / 335.0; }

	// Position
	virtual void setPosition(olc::vi2d point){ position = point; }
	virtual void movePosition(olc::vi2d otherPoint){ position += otherPoint; }
	virtual const olc::vi2d& getPosition(){ return position; }

	// Drawing
	virtual void draw() = 0;
};

#endif