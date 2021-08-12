#ifndef SCORECONTAINER_H
#define SCORECONTAINER_H

#define BASELEVEL 1

class ScoreContainer{
	olc::PixelGameEngine* pixelGameEngine;
	AnimationContainer* animationContainer;
	int level = BASELEVEL;
	int score = 0;


public:
	ScoreContainer(){}
	ScoreContainer(olc::PixelGameEngine& pge, AnimationContainer& ac)
	: pixelGameEngine(&pge), animationContainer(&ac){}

	void resetLevelAndScore(){
		level = BASELEVEL;
		score = 0;
	}

	int getLevel(){ return level; }
	int getScore(){ return score; }

	void incrementLevel(){
		// Increment level
		level++;

		// Add a +1 Animation
		int _scale = 4;
		olc::vi2d pos = pixelGameEngine->GetTextSize("Level - ") * _scale;
		int _maxFrames = 60;
		olc::Pixel _color = olc::BLACK;
		std::string text = "+1";
		int _dist = 50;
		Direction _dir = Direction::DOWNRIGHT;
		animationContainer->addHoveringTextAnimation(*pixelGameEngine, pos, _maxFrames, _color, text, _dist, _scale, _dir);
	}
	void addToScore(int amount){
		// Increment the score
		score += amount;

		// Add the +score animation
		int _scale = 4;
		olc::vi2d pos = pixelGameEngine->GetTextSize("Score - ") * _scale; pos.y = 0;
		int _maxFrames = 60;
		olc::Pixel _color = olc::BLACK;
		std::string text = "+" + std::to_string(amount);
		int _dist = 50;
		Direction _dir = Direction::DOWNLEFT;
		animationContainer->addHoveringTextAnimation(*pixelGameEngine, pos, _maxFrames, _color, text, _dist, _scale, _dir);
	}
};

#endif