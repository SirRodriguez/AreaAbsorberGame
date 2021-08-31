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
#include "derivedShapeList/BossCircleList.h"
#include "derivedShapeList/VortexList.h"

#include "../Direction.h"

//////////////
// Colors
//////////////

// 
// MainCircle
const olc::Pixel mainCircleColor = olc::BLUE;

// 
// Enemies
// 
const olc::Pixel otherCircleColor = olc::RED;
const olc::Pixel needleColor = olc::BLACK;
const olc::Pixel trapColor = olc::RED;
const olc::Pixel bossColor = olc::DARK_RED;

// 
// PowerUps
const olc::Pixel powerUpColor = olc::GREEN;
const olc::Pixel powerUpCircleColor = olc::VERY_DARK_BLUE;
const olc::Pixel buddyPowerUpColor = olc::GREEN;
const olc::Pixel buddyCircleColor = olc::DARK_BLUE;
const olc::Pixel circleCarColor = olc::GREEN;
const olc::Pixel circleCarWheelColor = olc::BLACK;
const olc::Pixel nukeColor = olc::BLACK;
const olc::Pixel nukePedalColor = olc::DARK_GREEN;

///////////////
// Speeds
///////////////

// 
// MainCircle
const uint8_t mainCircleSpeed = 5;

// 
// Enemies
const uint8_t otherCircleSpeed = 4;
const uint8_t needleSpeed = 6;
const uint8_t trapSpeed = 4;
const uint8_t bossSpeed = 2;

// 
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

// 
// MainCircle
const uint8_t initialMainCircleSize = 10;

// 
// Enemies
const uint8_t otherCircleMaxRadius = 50;
const uint8_t maxNeedleLength = 50;
const uint8_t trapLength = 40;

// 
// PowerUps
const uint8_t powerUpHeight = 50;
const uint8_t buddyPowerUpLength = 40;
const uint8_t circleCarRadius = 40;
const uint8_t nukeRadius = 30;

class ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	AnimationContainer* animationContainer;
	std::vector<ShapeList*> shapeLists;

public:
	ShapesContainer()
	: pixelGameEngine(nullptr), animationContainer(nullptr){}
	ShapesContainer(olc::PixelGameEngine& pge, AnimationContainer& ac)
	: pixelGameEngine(&pge), animationContainer(&ac){
		// Main circle
		shapeLists.push_back(
			new MainCircleList(
				pge, 
				ac, 
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
		// Power Ups
		shapeLists.push_back(new PowerUpList(pge, ac, powerUpColor, powerUpSpeed, powerUpHeight));
		#define powerUpsDef dynamic_cast<PowerUpList*>(shapeLists[1])
		// Circle Car power ups
		shapeLists.push_back(new CircleCarList(pge, ac, circleCarColor, circleCarWheelColor, circleCarSpeed, circleCarRadius));
		#define circleCarsDef dynamic_cast<CircleCarList*>(shapeLists[2])
		// Nukes
		shapeLists.push_back(new NukeList(pge, ac, nukeColor, nukePedalColor, nukeSpeed, nukeRadius));
		#define nukesDef dynamic_cast<NukeList*>(shapeLists[3])
		// Buddy Power ups
		shapeLists.push_back(new BuddyPowerUpList(pge, ac, buddyPowerUpColor, buddyPowerUpSpeed, buddyPowerUpLength));
		#define buddyPowerUpsDef dynamic_cast<BuddyPowerUpList*>(shapeLists[4])
		// Power Up Circles
		shapeLists.push_back(new PowerUpCircleList(pge, ac, powerUpCircleColor, powerUpCircleSpeed, 0));
		#define powerUpCirclesDef dynamic_cast<PowerUpCircleList*>(shapeLists[5])
		// Other circles
		shapeLists.push_back(new OtherCircleList(pge, ac, otherCircleColor, otherCircleSpeed, otherCircleMaxRadius));
		#define otherCirclesDef dynamic_cast<OtherCircleList*>(shapeLists[6])
		// Traps
		shapeLists.push_back(new TrapList(pge, ac, trapColor, trapSpeed, trapLength));
		#define trapsDef dynamic_cast<TrapList*>(shapeLists[7])
		// Needles
		shapeLists.push_back(new NeedleList(pge, ac, needleColor, needleSpeed, maxNeedleLength));
		#define needlesDef dynamic_cast<NeedleList*>(shapeLists[8])
		// Boss Circle
		shapeLists.push_back(new BossCircleList(pge, ac, bossColor, bossSpeed));
		#define bossCircleDef dynamic_cast<BossCircleList*>(shapeLists[9])
		// Vortexes
		shapeLists.push_back(new VortexList(pge, ac, olc::VERY_DARK_MAGENTA, olc::VERY_DARK_MAGENTA, 1, 25));
		#define vortexDef dynamic_cast<VortexList*>(shapeLists[10])
	}

	~ShapesContainer(){}

	void reset(){
		mainCircleDef->setRadius(initialMainCircleSize);
		mainCircleDef->resetObjects();

		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			(*it)->deleteAll();
	}

	void clearForNextLevel(){
		mainCircleDef->setRadius(initialMainCircleSize);

		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it)
			if((*it)->isEnemy() || (*it)->isObject())
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
	void addBoss(uint8_t dirFromCode){ bossCircleDef->add(dirFromCode); }
	void addVortex(uint8_t dirFromCode){ vortexDef->add(dirFromCode); }

	void addPowerUpCircles(){
		powerUpCirclesDef->add(mainCircleDef->getPosition(), mainCircleDef->getRadius());
	}

	// 
	// Moving Shapes
	// 

	void moveAllShapes(){
		for(auto it = shapeLists.begin(); it != shapeLists.end(); ++it){
			(*it)->moveAll();

			// Make enemies and main circle move towards vortex
			if((*it)->isEnemy() || (*it)->isMainCircle() || (*it)->isBuddy())
				(*it)->attract(*vortexDef);
		}
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

	// return 0 for no collision
	// return positive number for collision
	int checkCollisionForBossCircle(){
		return bossCircleDef->checkCollisionsWith(*mainCircleDef);
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