#ifndef HOVERINGTEXT_H
#define HOVERINGTEXT_H

#include "../../Direction.h"

class HoveringText : public Animation{
protected:
	olc::Pixel color;
	const std::string text;
	olc::vi2d textSize;
	int dist;
	int scale;
	olc::vf2d scaleV;
	Direction dir;

	olc::vi2d getLocOffset(){
		int d = (currentFrame * dist) / maxFrames;
		switch(dir){
			case Direction::UP: return olc::vi2d(0, -d);
			case Direction::DOWN: return olc::vi2d(0, d);
			case Direction::LEFT: return olc::vi2d(-d, 0);
			case Direction::RIGHT: return olc::vi2d(d, 0);
			case Direction::UPRIGHT: return olc::vi2d(d, -d);
			case Direction::UPLEFT: return olc::vi2d(-d, -d);
			case Direction::DOWNLEFT: return olc::vi2d(-d, d);
			case Direction::DOWNRIGHT: return olc::vi2d(d, d);
			default: return olc::vi2d(0, 0);
		}
	}

	void printText(){
		olc::vi2d loc = position + getLocOffset();
		olc::vf2d scaleV = { float(scale), float(scale) };

		pixelGameEngine->DrawStringDecal(
			loc,
			text,
			color,
			scaleV
		);
	}

public:
	HoveringText(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, const olc::Pixel _color, const std::string& _text, int _dist, int _scale, Direction _dir)
	: Animation(pge, pos, _maxFrames), 
		color(_color), 
		text(_text), 
		textSize(pixelGameEngine->GetTextSize(text)), 
		dist( _dist), 
		scale(_scale), 
		dir(_dir), 
		scaleV({float(_scale), float(_scale)}){}

	virtual ~HoveringText(){}

	virtual void drawFrame() override { printText(); }
};

#endif