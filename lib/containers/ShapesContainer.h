#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "../collisions.h"

#include "derivedShapeList/OtherCircleList.h"
#include "derivedShapeList/TrapList.h"
#include "derivedShapeList/NeedleList.h"
#include "derivedShapeList/NukeList.h"
#include "derivedShapeList/PowerUpList.h"
#include "derivedShapeList/CircleCarList.h"
#include "derivedShapeList/BuddyPowerUpList.h"
#include "derivedShapeList/PowerUpCircleList.h"
#include "derivedShapeList/MainCircleList.h"

#include "../Direction.h"

//////////////
// Colors
//////////////

// MainCircle
const olc::Pixel mainCircleColor = olc::BLACK;

// Enemies
const olc::Pixel otherCircleColor = olc::RED;
const olc::Pixel needleColor = olc::BLACK;
const olc::Pixel trapColor = olc::BLUE;

// PowerUps
const olc::Pixel powerUpColor = olc::GREEN;
const olc::Pixel powerUpCircleColor = olc::GREY;
const olc::Pixel buddyPowerUpColor = olc::YELLOW;
const olc::Pixel buddyCircleColor = olc::DARK_GREY;
const olc::Pixel circleCarColor = olc::BLUE;
const olc::Pixel circleCarWheelColor = olc::BLACK;
const olc::Pixel nukeColor = olc::BLACK;
const olc::Pixel nukePedalColor = olc::DARK_RED;

///////////////
// Speeds
///////////////

// MainCircle
const uint8_t mainCircleSpeed = 5;

// Enemies
const uint8_t otherCircleSpeed = 4;
const uint8_t needleSpeed = 6;
const uint8_t trapSpeed = 4;

// PowerUps
const uint8_t powerUpSpeed = 2;
const uint8_t powerUpCircleSpeed = 5;
const uint8_t buddyPowerUpSpeed = 2;
const uint8_t buddyCircleSpeed = 2;
const uint8_t circleCarSpeed = 2;
const uint8_t nukeSpeed = 6;

///////////////
// Sizes
///////////////

// MainCircle
const uint8_t initialMainCircleSize = 10;

// Enemies
const uint8_t otherCircleMaxRadius = 50;
const uint8_t maxNeedleLength = 50;
const uint8_t trapLength = 40;

// PowerUps
const uint8_t powerUpHeight = 50;
const uint8_t buddyPowerUpLength = 40;
const uint8_t circleCarRadius = 40;
const uint8_t nukeRadius = 30;

class ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	std::vector<ShapeList*> shapeLists;

public:
	ShapesContainer()
	: pixelGameEngine(nullptr){}
	ShapesContainer(olc::PixelGameEngine& pge)
	: pixelGameEngine(&pge){
		// Main circle
		shapeLists.push_back(
			new MainCircleList(
				pge, 
				mainCircleSpeed, 
				mainCircleColor, 
				initialMainCircleSize,
				circleCarColor,
				circleCarWheelColor,
				circleCarRadius,
				buddyCircleSpeed,
				buddyCircleColor
			)
		); 
		#define mainCircleDef dynamic_cast<MainCircleList*>(shapeLists[0])

		// Power ups
		shapeLists.push_back(new PowerUpList(pge, powerUpColor, powerUpSpeed, powerUpHeight));
		#define powerUpsDef dynamic_cast<PowerUpList*>(shapeLists[1])
		shapeLists.push_back(new CircleCarList(pge, circleCarColor, circleCarWheelColor, circleCarSpeed, circleCarRadius));
		#define circleCarsDef dynamic_cast<CircleCarList*>(shapeLists[2])
		shapeLists.push_back(new NukeList(pge, nukeColor, nukePedalColor, nukeSpeed, nukeRadius));
		#define nukesDef dynamic_cast<NukeList*>(shapeLists[3])
		shapeLists.push_back(new BuddyPowerUpList(pge, buddyPowerUpColor, buddyPowerUpSpeed, buddyPowerUpLength));
		#define buddyPowerUpsDef dynamic_cast<BuddyPowerUpList*>(shapeLists[4])

		// Buddies
		shapeLists.push_back(new PowerUpCircleList(pge, powerUpCircleColor, powerUpCircleSpeed, 0));
		#define powerUpCirclesDef dynamic_cast<PowerUpCircleList*>(shapeLists[5])

		// Enemies
		shapeLists.push_back(new OtherCircleList(pge, otherCircleColor, otherCircleSpeed, otherCircleMaxRadius));
		#define otherCirclesDef dynamic_cast<OtherCircleList*>(shapeLists[6])
		shapeLists.push_back(new TrapList(pge, trapColor, trapSpeed, trapLength));
		#define trapsDef dynamic_cast<TrapList*>(shapeLists[7])
		shapeLists.push_back(new NeedleList(pge, needleColor, needleSpeed, maxNeedleLength));
		#define needlesDef dynamic_cast<NeedleList*>(shapeLists[8])
	}

	// ~ShapesContainer(){
	// 	std::cout << "Called Destructor" << std::endl;
	// 	for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it){
	// 		delete *it;
	// 	}
	// }

	void reset(){
		mainCircleDef->setRadius(initialMainCircleSize);
		mainCircleDef->resetObjects();

		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			(*it)->deleteAll();
	}

	void clearForNextLevel(){
		mainCircleDef->setRadius(initialMainCircleSize);

		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			if((*it)->isEnemy())
				(*it)->deleteAll();
	}

	// 
	// Drawing
	// 

	void hideAll(){
		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			(*it)->hideAll();
	}

	void drawAllShapes(){
		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			(*it)->drawAll();
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
	void addCircle(uint8_t dirFromCode){ otherCirclesDef->add(dirFromCode); }
	void addPowerUp(uint8_t dirFromCode){ powerUpsDef->add(dirFromCode); }
	void addNeedle(uint8_t dirFromCode){ needlesDef->add(dirFromCode); }
	void addBuddyPowerUp(uint8_t dirFromCode){ buddyPowerUpsDef->add(dirFromCode); }
	void addTrap(uint8_t dirFromCode){ trapsDef->add(dirFromCode); }
	void addCircleCar(uint8_t dirFromCode){ circleCarsDef->add(dirFromCode); }
	void addNuke(uint8_t dirFromCode){ nukesDef->add(dirFromCode); }

	void addPowerUpCircles(){
		powerUpCirclesDef->add(mainCircleDef->getPosition(), mainCircleDef->getRadius());
	}

	// 
	// Moving Shapes
	// 

	void moveAllShapes(){
		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			(*it)->moveAll();
	}

	// 
	// Collision detection
	// 

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollisionForCircle(){
		int collideNum = otherCirclesDef->checkCollisionsWith(*mainCircleDef);
		if(mainCircleDef->inCar()){
			mainCircleDef->hitCar(collideNum);
			return collideNum;
		}
		return collideNum > mainCircleDef->getRadius() ? -1 : collideNum;
	}

	// Return 0 for no collision
	// NEW: Return the value of the collided circle
	int checkCollisionForPowerUpCircles(){
		return otherCirclesDef->checkCollisionsWith(*powerUpCirclesDef);
	}

	// Returns 1 for collision
	// Returns 0 for no colision
	int checkCollisionForPowerUps(){
		return powerUpsDef->checkCollisionsWith(*mainCircleDef) > 0 ? 1 : 0;
	}

	// Returns 0 for no collision
	// Returns 1 for collision with other circle
	// Returns 2 for collision with power up circles
	// Returns -1 for collision with main circle
	// Returns -2 for collision with buddy circle
	// Returns -3 for collision with trap on main circle
	// Returns -4 for collision with main circle car
	int checkCollisionForNeedles(){
		if(mainCircleDef->inCar()){
			if(needlesDef->checkCollisionsWith(mainCircleDef->getCar()) > 0){
				return -4;
			}
		}

		if(mainCircleDef->isTrapped()){
			if(needlesDef->checkCollisionsWith(mainCircleDef->getTrapSquare(), false) > 0){
				return -3;
			}
		}

		if(needlesDef->checkCollisionsWith(*mainCircleDef, false) > 0){
			return -1;
		}

		if(needlesDef->checkCollisionsWith(*otherCirclesDef, false) > 0){
			return 1;
		}

		if(needlesDef->checkCollisionsWith(*powerUpCirclesDef, false)> 0){
			return 2;
		}

		if(mainCircleDef->buddyAlive()){
			if(needlesDef->checkCollisionsWith(mainCircleDef->getBuddy(), false) > 0){
				return -2;
			}
		}

		return 0;
	}

	// Returns 0 for no collision
	// Returns -1 for collision with main circle
	int checkCollisionForBuddyPowerUps(){
		return buddyPowerUpsDef->checkCollisionsWith(*mainCircleDef) > 0 ? -1 : 0;
	}

	// Return 0 for no collision
	// Return negative number for Collision with other circle thats bigger
	// Return positive number for collision with other circle thats smaller
	int checkCollisionForBuddyCircle(){
		if(mainCircleDef->buddyAlive()){
			int collideNum = otherCirclesDef->checkCollisionsWith(mainCircleDef->getBuddy());
			if(mainCircleDef->getBuddyRadius() < collideNum){
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
		int collideNum = trapsDef->checkCollisionsWith(*mainCircleDef);
		if(collideNum > 0){
			mainCircleDef->activateTrap();
			return -1;
		}
		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForCircleCars(){
		if(circleCarsDef->checkCollisionsWith(*mainCircleDef) > 0){
			mainCircleDef->activateCar();
			return -1;
		}
		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForNukes(){
		return nukesDef->checkCollisionsWith(*mainCircleDef) > 0 ? -1 : 0;
	}

	// 
	// Shape changes
	// 

	// Main Circle
	void resetMainCirclePosition(){
		mainCircleDef->setPosition(olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2));
	}

	void growMainCircle(int amount){
		mainCircleDef->grow(amount);
	}

	// Main Circle Car
	void killMainCircleCar(){
		mainCircleDef->inactivateCar();
	}

	// Buddy Circle
	void resetBuddyCircle(){
		mainCircleDef->killBuddy();
	}

	void addLifeToBuddyCircle(int amount){
		mainCircleDef->addLifeToBuddy(amount);
	}

	void subtractLifeToBuddyCircle(int amount){
		mainCircleDef->reduceLifeToBuddy(amount);
	}

	// Nuke
	void runNuke(){
		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			if((*it)->isEnemy())
				(*it)->deleteAll();
	}

	// 
	// Checks
	// 

	bool mainCircleTooBig(){
		return mainCircleDef->getRadius() >= 50;
	}

	int getMainCircleCarLife(){
		return mainCircleDef->getCarLife();
	}
};

#endif