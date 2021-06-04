#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "ShapesContainer.h"
#include "ScoreContainer.h"

// likelyHoodOfCircles = 50;
// likelyHoodOfPowerUps = 500;
// likelyHoodOfNeedles = 1000;
// likelyHoodOfBuddyPowerUps = 1000;

class ShapeGenerator{
	ShapesContainer* shapesContainer;
	ScoreContainer* scoreContainer;

	// Likelyhood of shapes generated
	int likelyHoodOfCircles = 0;
	int likelyHoodOfPowerUps = 0;
	int likelyHoodOfNeedles = 0;
	int likelyHoodOfBuddyPowerUps = 0;

	bool generateChecker(int likelyHood){
		int module = likelyHood - (scoreContainer->getLevel() - 1) * likelyHood / 10;
		if(module > 0){
			if(rand() % module == 0){
				return true;
			}
		}else{
			if(rand() % (likelyHood / 10) == 0){
				return true;
			}
		}

		return false;
	}

	// 
	// Generation functions
	// 
	void generateCircles(){
		if(generateChecker(likelyHoodOfCircles))
			shapesContainer->addCircle();
	}

	void generatePowerUps(){
		if(generateChecker(likelyHoodOfPowerUps))
			shapesContainer->addPowerUp();
	}

	void generateNeedles(){
		if(generateChecker(likelyHoodOfNeedles))
			shapesContainer->addNeedle();
	}

	void generateBuddyPowerUps(){
		if(generateChecker(likelyHoodOfBuddyPowerUps))
			shapesContainer->addBuddyPowerUp();
	}

public:
	ShapeGenerator()
	: shapesContainer(nullptr), scoreContainer(nullptr){
		srand(time(0));
	}
	ShapeGenerator(ShapesContainer& newShapesContainer, ScoreContainer& newScoreContainer)
	: shapesContainer(&newShapesContainer), scoreContainer(&newScoreContainer){
		srand(time(0));
	}

	void setLikelyHoodOfCircles(int value){ likelyHoodOfCircles = value; }
	void setLikelyHoodOfPowerUps(int value){ likelyHoodOfPowerUps = value; }
	void setLikelyHoodOfNeedles(int value){ likelyHoodOfNeedles = value; }
	void setLikelyHoodOfBuddyPowerUps(int value){ likelyHoodOfBuddyPowerUps = value; }

	void runShapeGenerationFrame(){
		generateCircles();
		generatePowerUps();
		generateNeedles();
		generateBuddyPowerUps();
	}
};

#endif