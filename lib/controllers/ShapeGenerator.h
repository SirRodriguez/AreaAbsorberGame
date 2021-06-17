#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "..\containers\ShapesContainer.h"
#include "..\containers\ScoreContainer.h"

class ShapeGenerator{
	ShapesContainer* shapesContainer;
	ScoreContainer* scoreContainer;

	// Likelyhood of shapes generated
	int likelyHoodOfCircles = 50;
	int likelyHoodOfPowerUps = 500;
	int likelyHoodOfNeedles = 1000;
	int likelyHoodOfBuddyPowerUps = 1000;
	int likelyHoodOfTraps = 500;

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

	uint8_t makeDirectionCode(){
		uint8_t code = 0x01;
		int level = scoreContainer->getLevel();

		if(level <= 10){
			// Code does not change
		}else if(level <= 15){
			code = code << rand() % 2;
		}else if(level <= 20){
			code = code << rand() % 3;
		}else if(level <= 25){
			code = code << rand() % 4;
		}else if(level <= 30){
			code = code << rand() % 5;
		}else if(level <= 35){
			code = code << rand() % 6;
		}else if(level <= 40){
			code = code << rand() % 7;
		}else{
			code = code << rand() % 8;
		} // for if statements if there is more

		return code;
	}

	// 
	// Generation functions
	// 
	void generateCircles(){
		if(generateChecker(likelyHoodOfCircles))
			shapesContainer->addCircle(makeDirectionCode());
	}

	void generatePowerUps(){
		if(generateChecker(likelyHoodOfPowerUps))
			shapesContainer->addPowerUp(makeDirectionCode());
	}

	void generateNeedles(){
		if(generateChecker(likelyHoodOfNeedles))
			shapesContainer->addNeedle(makeDirectionCode());
	}

	void generateBuddyPowerUps(){
		if(generateChecker(likelyHoodOfBuddyPowerUps))
			shapesContainer->addBuddyPowerUp(makeDirectionCode());
	}

	void generateTraps(){
		if(generateChecker(likelyHoodOfTraps))
			shapesContainer->addTrap(makeDirectionCode());
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

	void runShapeGenerationFrame(){
		generateCircles();
		generatePowerUps();
		generateNeedles();
		generateBuddyPowerUps();
		generateTraps();
	}
};

#endif