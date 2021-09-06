#ifndef ANIMATIONCONTAINER_H
#define ANIMATIONCONTAINER_H

#include <queue>

#include "../Direction.h"
#include "../animations/Animation.h"
#include "../animations/derivedAnimations/Pop.h"
#include "../animations/derivedAnimations/HoveringText.h"

class AnimationContainer{
protected:
	std::queue<Animation*> popStorage;
	std::list<Animation*> animations;

public:
	AnimationContainer(){}
	~AnimationContainer(){
		for(auto it = animations.begin(); it != animations.end(); ++it)
			delete *it;

		while(!popStorage.empty()){
			delete popStorage.front();
			popStorage.pop();
		}
	}

	void initializePopStorage(olc::PixelGameEngine& pge){
		int storageSize = 50;

		olc::vi2d pos = olc::vi2d(0,0);
		int maxFrames = 60;
		olc::Pixel lineColor = olc::BLACK;
		int radius = 50;
		int numLines = 8;
		double degOffset = 0.0;
		for(int i = 0; i < storageSize; ++i)
			popStorage.push(new Pop(pge, pos, maxFrames, lineColor, radius, numLines, degOffset));
	}

	// 
	// Drawing
	// 
	void drawAnimationsFrame(){
		for(auto it = animations.begin(); it != animations.end();){
			(*it)->drawFrame();
			(*it)->incrementFrame();
			if((*it)->framesMaxed()){
				Animation* an = *it;
				animations.erase(it++);
				delete an;
			}else{
				++it;
			}
		}
	}

	// 
	// Adding Animations
	// 
	void addPopAnimation(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, olc::Pixel _lineColor, int _radius, int _numLines, double _degOffset){
		animations.push_back(new Pop(pge, pos, _maxFrames, _lineColor, _radius, _numLines, _degOffset));
	}
	void addHoveringTextAnimation(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, olc::Pixel _color, std::string text, int _dist, int _scale, Direction _dir){
		animations.push_back(new HoveringText(pge, pos, _maxFrames, _color, text, _dist, _scale, _dir));
	}
};

#endif