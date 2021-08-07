#ifndef ANIMATIONCONTAINER_H
#define ANIMATIONCONTAINER_H

#include "../animations/Animation.h"
#include "../animations/derivedAnimations/Pop.h"
#include "../animations/derivedAnimations/HoveringText.h"

class AnimationContainer{
protected:
	std::list<Animation*> animations;

public:
	AnimationContainer(){}
	~AnimationContainer(){}

	// 
	// Drawing
	// 
	void drawAnimationsFrame(){
		for(auto it = animations.begin(); it != animations.end();){
			(*it)->drawFrame();
			(*it)->incrementFrame();
			if((*it)->framesMaxed()){
				(*it)->clear();
				Animation* an = *it;
				animations.erase(it++);
				delete an;
			}else{
				++it;
			}
		}
	}

	void clearAnimations(){
		for(auto it = animations.begin(); it != animations.end(); ++it){
			(*it)->clear();
		}
	}

	// 
	// Adding Animations
	// 
	void addPopAnimation(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, olc::Pixel _lineColor, int _radius, int _numLines, double _degOffset){
		animations.push_back(new Pop(pge, pos, _maxFrames, _lineColor, _radius, _numLines, _degOffset));
	}
	void addHoveringTextAnimation(olc::PixelGameEngine& pge, olc::vi2d& pos, int _maxFrames, olc::Pixel _color, std::string text, int _height, int _scale){
		animations.push_back(new HoveringText(pge, pos, _maxFrames, _color, text, _height, _scale));
	}
};

#endif