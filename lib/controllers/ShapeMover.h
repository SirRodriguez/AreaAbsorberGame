#ifndef SHAPEMOVER_H
#define SHAPEMOVER_H

#include "..\containers\ShapesContainer.h"

class ShapeMover{
	ShapesContainer* shapesContainer;

	int otherCircleSpeed = 0;
	int powerUpSpeed = 0;
	int powerUpCircleSpeed = 0;
	int needleSpeed = 0;
	int buddyPowerUpSpeed = 0;
	int buddyCircleSpeed = 0;
	int MainCircleSpeed = 0;

	void moveShapesDown(){
		shapesContainer->moveCircles(otherCircleSpeed);
		shapesContainer->movePowerUps(powerUpSpeed);
		shapesContainer->movePowerUpCircles(powerUpCircleSpeed);
		shapesContainer->moveNeedles(needleSpeed);
		shapesContainer->moveBuddyPowerUps(buddyPowerUpSpeed);
		shapesContainer->moveBuddyCircle(buddyCircleSpeed);
	}

	void moveMainCircle(){
		// Uses user input
		// Update the position of the circle
		// if(upButton.bHeld){
		// 	shapesContainer->moveMainCircleUp(MainCircleSpeed);
		// }
		// if(downButton.bHeld){
		// 	shapesContainer->moveMainCircleDown(MainCircleSpeed);
		// }
		// if(leftButton.bHeld){
		// 	shapesContainer->moveMainCircleLeft(MainCircleSpeed);
		// }
		// if(rightButton.bHeld){
		// 	shapesContainer->moveMainCircleRight(MainCircleSpeed);
		// }
		shapesContainer->moveMainCircle(MainCircleSpeed);
	}

public:
	ShapeMover()
	: shapesContainer(nullptr){}
	ShapeMover(ShapesContainer& _shapesContainer)
	: shapesContainer(&_shapesContainer){}

	void setOtherCircleSpeed(int value){ otherCircleSpeed = value; }
	void setPowerUpSpeed(int value){ powerUpSpeed = value; }
	void setPowerUpCircleSpeed(int value){ powerUpCircleSpeed = value; }
	void setNeedleSpeed(int value){ needleSpeed = value; }
	void setBuddyPowerUpSpeed(int value){ buddyPowerUpSpeed = value; }
	void setBuddyCircleSpeed(int value){ buddyCircleSpeed = value; }
	void setMainCircleSpeed(int value){ MainCircleSpeed = value; }

	void runMoveShapesFrame(){
		moveShapesDown();
		moveMainCircle();
	}
};

#endif