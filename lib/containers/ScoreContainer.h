#ifndef SCORECONTAINER_H
#define SCORECONTAINER_H

#define BASELEVEL 1

class ScoreContainer{
	int level = BASELEVEL;
	int score = 0;

public:
	ScoreContainer(){}

	void resetLevelAndScore(){
		level = BASELEVEL;
		score = 0;
	}

	int getLevel(){ return level; }
	int getScore(){ return score; }

	void incrementLevel(){ level++; }
	void addToScore(int amount){ score += amount; }
};

#endif