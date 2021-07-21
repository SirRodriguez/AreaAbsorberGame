#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "../utils.h"

#include "derivedShapeList/OtherCircleList.h"
#include "derivedShapeList/TrapList.h"
#include "derivedShapeList/NeedleList.h"
#include "derivedShapeList/NukeList.h"
#include "derivedShapeList/PowerUpList.h"
#include "derivedShapeList/CircleCarList.h"
#include "derivedShapeList/BuddyPowerUpList.h"
#include "derivedShapeList/PowerUpCircleList.h"
#include "derivedShapeList/MainCircleList.h"

// Colors
const olc::Pixel mainCircleColor = olc::BLACK;
const olc::Pixel otherCircleColor = olc::RED;
const olc::Pixel powerUpColor = olc::GREEN;
const olc::Pixel powerUpCircleColor = olc::GREY;
const olc::Pixel needleColor = olc::BLACK;
const olc::Pixel buddyPowerUpColor = olc::YELLOW;
const olc::Pixel buddyCircleColor = olc::DARK_GREY;
const olc::Pixel trapColor = olc::BLUE;
const olc::Pixel circleCarColor = olc::BLUE;
const olc::Pixel circleCarWheelColor = olc::BLACK;
const olc::Pixel nukeColor = olc::BLACK;
const olc::Pixel nukePedalColor = olc::DARK_RED;

// Speeds
const uint8_t otherCircleSpeed = 4;
const uint8_t powerUpSpeed = 2;
const uint8_t powerUpCircleSpeed = 5;
const uint8_t needleSpeed = 6;
const uint8_t buddyPowerUpSpeed = 2;
const uint8_t buddyCircleSpeed = 2;
const uint8_t mainCircleSpeed = 5;
const uint8_t trapSpeed = 4;
const uint8_t circleCarSpeed = 2;
const uint8_t nukeSpeed = 6;

// Sizes
const uint8_t initialMainCircleSize = 10;
const uint8_t otherCircleMaxRadius = 50;
const uint8_t powerUpHeight = 50;
const uint8_t maxNeedleLength = 50;
const uint8_t buddyPowerUpLength = 40;
const uint8_t trapLength = 40;
const uint8_t circleCarRadius = 40;
const uint8_t nukeRadius = 30;

class ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;

	// Main circle
	// MainCircle mainCircle;
	MainCircleList mainCircle;

	// Power ups
	PowerUpList powerUps;
	CircleCarList circleCars;
	BuddyPowerUpList buddyPowerUps;
	PowerUpCircleList powerUpCircles;
	NukeList nukes;

	// Enemies
	NeedleList needles;
	TrapList traps;
	OtherCircleList otherCircles;

public:
	ShapesContainer()
	: pixelGameEngine(nullptr){}
	ShapesContainer(olc::PixelGameEngine& pge)
	: pixelGameEngine(&pge){
		mainCircle = MainCircleList(pge);

		powerUps = PowerUpList(pge);
		circleCars = CircleCarList(pge);
		nukes = NukeList(pge);
		buddyPowerUps = BuddyPowerUpList(pge);
		powerUpCircles = PowerUpCircleList(pge);

		otherCircles = OtherCircleList(pge);
		traps = TrapList(pge);
		needles = NeedleList(pge);

		// Make sure that the lists are cleared
		otherCircles.deleteAll();
		powerUps.deleteAll();
		powerUpCircles.deleteAll();
		needles.deleteAll();
		buddyPowerUps.deleteAll();
		traps.deleteAll();
		circleCars.deleteAll();
		nukes.deleteAll();
	}

	void reset(){
		mainCircle.setRadius(initialMainCircleSize);
		mainCircle.resetObjects();

		otherCircles.deleteAll();
		powerUps.deleteAll();
		buddyPowerUps.deleteAll();
		powerUpCircles.deleteAll();
		needles.deleteAll();
		traps.deleteAll();
		circleCars.deleteAll();
		nukes.deleteAll();
	}

	void clearForNextLevel(){
		mainCircle.setRadius(initialMainCircleSize);
		otherCircles.deleteAll();
		needles.deleteAll();
		traps.deleteAll();
	}

	// 
	// Drawing
	// 

	void hideAll(){
		mainCircle.hideAll();
		otherCircles.hideAll();
		powerUps.hideAll();
		powerUpCircles.hideAll();
		needles.hideAll();
		buddyPowerUps.hideAll();
		traps.hideAll();
		circleCars.hideAll();
		nukes.hideAll();
	}

	void drawAllShapes(){
		mainCircle.drawAll();
		otherCircles.drawAll();
		powerUps.drawAll();
		powerUpCircles.drawAll();
		needles.drawAll();
		buddyPowerUps.drawAll();
		traps.drawAll();
		circleCars.drawAll();
		nukes.drawAll();
	}

	// 
	// List additions
	// 

	// Direction code tells the direction where the shape is comming from on the screen
	// It is a bitwise code, so:
	// 0000 0000 <- from right to left, if the bit is a 1 it means:
	// - From Top
	// - From Bottom
	// - From Left
	// - From Right
	// - From Top Left
	// - From Top Right
	// - Form Bottom Left
	// - From Bottom Right
	// If multiple bits are one, them multiple circles will pop out
	void addCircle(uint8_t dirFromCode){ otherCircles.add(dirFromCode); }
	void addPowerUp(uint8_t dirFromCode){ powerUps.add(dirFromCode); }
	void addNeedle(uint8_t dirFromCode){ needles.add(dirFromCode); }
	void addBuddyPowerUp(uint8_t dirFromCode){ buddyPowerUps.add(dirFromCode); }
	void addTrap(uint8_t dirFromCode){ traps.add(dirFromCode); }
	void addCircleCar(uint8_t dirFromCode){ circleCars.add(dirFromCode); }
	void addNuke(uint8_t dirFromCode){ nukes.add(dirFromCode); }

	void addPowerUpCircles(){
		powerUpCircles.add(mainCircle.getPosition(), mainCircle.getRadius());
	}

	// 
	// Moving Shapes
	// 

	void moveAllShapes(){
		mainCircle.moveAll();
		otherCircles.moveAll();
		powerUps.moveAll();
		powerUpCircles.moveAll();
		needles.moveAll();
		buddyPowerUps.moveAll();
		traps.moveAll();
		circleCars.moveAll();
		nukes.moveAll();
	}

	// 
	// Collision detection
	// 

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollisionForCircle(){
		int collideNum = otherCircles.checkCollisionsWith(mainCircle);
		if(mainCircle.inCar()){
			mainCircle.hitCar(collideNum);
			return collideNum;
		}
		return collideNum > mainCircle.getRadius() ? -1 : collideNum;
	}

	// Return 0 for no collision
	// NEW: Return the value of the collided circle
	int checkCollisionForPowerUpCircles(){
		return otherCircles.checkCollisionsWith(powerUpCircles);
	}

	// Returns 1 for collision
	// Returns 0 for no colision
	int checkCollisionForPowerUps(){
		return powerUps.checkCollisionsWith(mainCircle) > 0 ? 1 : 0;
	}

	// Returns 0 for no collision
	// Returns 1 for collision with other circle
	// Returns 2 for collision with power up circles
	// Returns -1 for collision with main circle
	// Returns -2 for collision with buddy circle
	// Returns -3 for collision with trap on main circle
	// Returns -4 for collision with main circle car
	int checkCollisionForNeedles(){
		if(mainCircle.inCar()){
			if(needles.checkCollisionsWith(mainCircle.getCar()) > 0){
				return -4;
			}
		}

		if(mainCircle.isTrapped()){
			if(needles.checkCollisionsWith(mainCircle.getTrapSquare(), false) > 0){
				return -3;
			}
		}

		if(needles.checkCollisionsWith(mainCircle, false) > 0){
			return -1;
		}

		if(needles.checkCollisionsWith(otherCircles, false) > 0){
			return 1;
		}

		if(needles.checkCollisionsWith(powerUpCircles, false)> 0){
			return 2;
		}

		if(mainCircle.buddyAlive()){
			if(needles.checkCollisionsWith(mainCircle.getBuddy(), false) > 0){
				return -2;
			}
		}

		return 0;
	}

	// Returns 0 for no collision
	// Returns -1 for collision with main circle
	int checkCollisionForBuddyPowerUps(){
		return buddyPowerUps.checkCollisionsWith(mainCircle) > 0 ? -1 : 0;
	}

	// Return 0 for no collision
	// Return negative number for Collision with other circle thats bigger
	// Return positive number for collision with other circle thats smaller
	int checkCollisionForBuddyCircle(){
		if(mainCircle.buddyAlive()){
			int collideNum = otherCircles.checkCollisionsWith(mainCircle.getBuddy());
			if(mainCircle.getBuddyRadius() < collideNum){
				return -1;
			}else{
				return collideNum;
			}
		}
		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForTraps(){
		int collideNum = traps.checkCollisionsWith(mainCircle);
		if(collideNum > 0){
			mainCircle.activateTrap(collideNum);
			return -1;
		}
		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForCircleCars(){
		if(circleCars.checkCollisionsWith(mainCircle) > 0){
			mainCircle.activateCar();
			return -1;
		}
		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForNukes(){
		return nukes.checkCollisionsWith(mainCircle) > 0 ? -1 : 0;
	}

	// 
	// Shape changes
	// 

	// Main Circle
	void resetMainCirclePosition(){
		mainCircle.setPosition(olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2));
	}

	void growMainCircle(int amount){
		mainCircle.grow(amount);
	}

	// Main Circle Car
	void killMainCircleCar(){
		mainCircle.inactivateCar();
	}

	// Buddy Circle
	void resetBuddyCircle(){
		mainCircle.killBuddy();
	}

	void addLifeToBuddyCircle(int amount){
		mainCircle.addLifeToBuddy(amount);
	}

	void subtractLifeToBuddyCircle(int amount){
		mainCircle.reduceLifeToBuddy(amount);
	}

	// Nuke
	void runNuke(){
		needles.deleteAll();
		traps.deleteAll();
		otherCircles.deleteAll();
	}

	// 
	// Checks
	// 

	bool mainCircleTooBig(){
		return mainCircle.getRadius() >= 50;
	}

	int getMainCircleCarLife(){
		return mainCircle.getCarLife();
	}
};

#endif