#ifndef SCORECONTAINER_H
#define SCORECONTAINER_H

class ScoreContainer{
	int level = 1;
	int score = 0;

public:
	ScoreContainer(){}

	void resetLevelAndScore(){
		level = 1;
		score = 0;
	}

	int getLevel(){ return level; }
	int getScore(){ return score; }

	void incrementLevel(){ level++; }
	void addToScore(int amount){ score += amount; }
};

#endif