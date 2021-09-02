#ifndef POP_H
#define POP_H

#include "../Animation.h"
#include "../shapes/derivedAnimationShape/AnimationLine.h"

class Pop: public Animation{
protected:
	olc::Pixel lineColor;
	int radius;
	int numLines;
	std::list<AnimationLine*> lines;
	double degOffset;

	olc::vi2d getLocationOffsetFromDeg(int r, double d){
		int x = r * std::cos(d * PI() / 180);
		int y = r * std::sin(d * PI() / 180);
		return olc::vi2d(x, y);
	}

public:
	Pop(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, olc::Pixel _lineColor, int _radius, int _numLines, double _degOffset)
	: Animation(pge, pos, _maxFrames), lineColor(_lineColor), radius(_radius), numLines(_numLines), degOffset(_degOffset){
		for(int i = 0; i < numLines; ++i)
			lines.push_back(new AnimationLine(pge, position, lineColor, 0, 0));
	}

	virtual ~Pop(){
		for(auto it = lines.begin(); it != lines.end(); ++it)
			delete *it;
	}

	// PI
	double PI(){ return 355.0 / 113.0; }
	double RECPI(){ return 113.0 / 335.0; }

	virtual void drawFrame() override {
		if(numLines > 0){
			double increment = 360 / numLines;
			double deg = increment + degOffset;
			int distFromCenter = (currentFrame * radius) / maxFrames;
			int dx = std::min(distFromCenter, radius - distFromCenter);
			int dy = dx;

			for(auto it = lines.begin(); it != lines.end(); ++it){
				olc::vi2d locOffset = getLocationOffsetFromDeg(distFromCenter, deg);
				olc::vi2d loc = position + locOffset;
				(*it)->setPosition(loc);

				(*it)->setdx(dx * std::cos(deg * PI() / 180));
				(*it)->setdy(dy * std::sin(deg * PI() / 180));

				(*it)->draw();

				deg += increment;
			}
		}
	}
};

#endif