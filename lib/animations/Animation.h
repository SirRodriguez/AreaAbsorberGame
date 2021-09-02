#ifndef ANIMATION_H
#define ANIMATION_H

class Animation{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	int maxFrames;
	int currentFrame;

public:
	Animation(olc::PixelGameEngine& pge, olc::vi2d& pos, int newmaxFrames)
	: pixelGameEngine(&pge), position(pos), maxFrames(newmaxFrames), currentFrame(0){}

	virtual ~Animation(){}

	void incrementFrame(){ ++currentFrame; }
	void decrementFrame(){ --currentFrame; }
	virtual void drawFrame() = 0;

	bool framesMaxed(){ return currentFrame >= maxFrames; }
};

#endif