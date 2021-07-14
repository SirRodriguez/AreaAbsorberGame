#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "../objects/mainCircle/MainCircle.h"
#include "../objects/powerUp/PowerUpCircle.h"
#include "../objects/BuddyPowerUp.h"
#include "../objects/CircleCar.h"

#include "../utils.h"

#include "derivedShapeList/OtherCircleList.h"
#include "derivedShapeList/TrapList.h"
#include "derivedShapeList/NeedleList.h"
#include "derivedShapeList/NukeList.h"
#include "derivedShapeList/PowerUpList.h"

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
	MainCircle mainCircle;

	// Power ups
	PowerUpList powerUps;
	std::list<CircleCar> circleCars;
	std::list<BuddyPowerUp> buddyPowerUps;
	std::list<PowerUpCircle> powerUpCircles;
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
		olc::vi2d centerPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);

		// Initialize the main circle and buddy circle
		uint8_t numLives = 0;
		mainCircle = MainCircle(
			pge, 
			centerPos, 
			mainCircleSpeed, 
			mainCircleColor, 
			initialMainCircleSize, 
			numLives,
			circleCarColor,
			circleCarWheelColor,
			circleCarRadius,
			buddyCircleSpeed,
			buddyCircleColor
		);

		powerUps = PowerUpList(pge);
		nukes = NukeList(pge);

		otherCircles = OtherCircleList(pge);
		traps = TrapList(pge);
		needles = NeedleList(pge);

		// Make sure that the lists are cleared
		otherCircles.deleteAll();
		powerUps.deleteAll();
		deleteAllPowerUpCircles();
		needles.deleteAll();
		deleteAllBuddyPowerUps();
		traps.deleteAll();
		deleteAllCircleCars();
		nukes.deleteAll();
	}

	void reset(){
		setMainCircleRadius(initialMainCircleSize);
		resetMainCircleObjects();

		otherCircles.deleteAll();
		powerUps.deleteAll();
		deleteAllBuddyPowerUps();
		deleteAllPowerUpCircles();
		needles.deleteAll();
		traps.deleteAll();
		deleteAllCircleCars();
		nukes.deleteAll();
	}

	void clearForNextLevel(){
		setMainCircleRadius(initialMainCircleSize);
		otherCircles.deleteAll();
		needles.deleteAll();
		traps.deleteAll();
	}

	// 
	// Drawing
	// 

	void hideMainCircle(){
		mainCircle.clear();
	}

	void hidePowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->clear();
		}
	}

	void hideBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->clear();
		}
	}

	void hideCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->clear();
		}
	}

	void hideAll(){
		hideMainCircle();
		otherCircles.hideAll();
		powerUps.hideAll();
		hidePowerUpCircles();
		needles.hideAll();
		hideBuddyPowerUps();
		traps.hideAll();
		hideCircleCars();
		nukes.hideAll();
	}

	void drawMainCircle(){
		mainCircle.draw();
	}

	void drawPowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->draw();
		}
	}

	void drawBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->draw();
		}
	}

	void drawCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->draw();
		}
	}

	void drawAllShapes(){
		drawMainCircle();
		otherCircles.drawAll();
		powerUps.drawAll();
		drawPowerUpCircles();
		needles.drawAll();
		drawBuddyPowerUps();
		traps.drawAll();
		drawCircleCars();
		nukes.drawAll();
	}

	// 
	// List additions
	// 

	void addCircle(uint8_t dirFromCode){
		otherCircles.add(dirFromCode);
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addPowerUp(uint8_t dirFromCode){
		powerUps.add(dirFromCode);
	}

	void addPowerUpCircles(){
		olc::vi2d pos = mainCircle.getPosition();
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 0));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 1));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 2));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 3));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 4));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 5));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 6));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, powerUpCircleSpeed, powerUpCircleColor, mainCircle.getRadius(), 7));
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addNeedle(uint8_t dirFromCode){
		needles.add(dirFromCode);
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addBuddyPowerUp(uint8_t dirFromCode){
		auto makeBuddyPowerUp = [&](olc::vi2d _loc, int dirCode){
			buddyPowerUps.push_back(BuddyPowerUp(*pixelGameEngine, _loc, buddyCircleSpeed, buddyPowerUpColor, buddyPowerUpLength, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeBuddyPowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeBuddyPowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeBuddyPowerUp(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeBuddyPowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeBuddyPowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeBuddyPowerUp(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeBuddyPowerUp(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeBuddyPowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeBuddyPowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeBuddyPowerUp(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeBuddyPowerUp(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeBuddyPowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
			}
		}
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addTrap(uint8_t dirFromCode){
		traps.add(dirFromCode);
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addCircleCar(uint8_t dirFromCode){
		auto makeCircleCar = [&](olc::vi2d _loc, int dirCode){
			// const uint8_t circleCarNumWheels = 4;
			// const double degOffset = 45.0;
			circleCars.push_back(CircleCar(*pixelGameEngine, _loc, circleCarSpeed, circleCarColor, circleCarWheelColor, circleCarRadius, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeCircleCar(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeCircleCar(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeCircleCar(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeCircleCar(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeCircleCar(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeCircleCar(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeCircleCar(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeCircleCar(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeCircleCar(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeCircleCar(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeCircleCar(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeCircleCar(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
			}
		}
	}

	// Direction code tells the direction where the power up is comming from on the screen
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
	void addNuke(uint8_t dirFromCode){
		nukes.add(dirFromCode);
	}

	// 
	// Moving Shapes
	// 
	void moveMainCircle(){
		mainCircle.move();
	}

	void movePowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end();){
			it->move();
			if(it->outOfBounds()){
				powerUpCircles.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end();){
			it->move();
			if(it->outOfBounds()){
				buddyPowerUps.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end();){
			it->move();
			if(it->outOfBounds()){
				circleCars.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveAllShapes(){
		moveMainCircle();
		otherCircles.moveAll();
		powerUps.moveAll();
		movePowerUpCircles();
		needles.moveAll();
		moveBuddyPowerUps();
		traps.moveAll();
		moveCircleCars();
		nukes.moveAll();
	}

	// 
	// Collision detection
	// 

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollisionForCircle(){
		int collideNum = 0;
		if(mainCircle.inCar()){
			collideNum = otherCircles.checkCollisionsWith(mainCircle.getCar());
			if(collideNum > 0){
				mainCircle.hitCar(collideNum);
			}

			return collideNum;

		}else{
			collideNum = otherCircles.checkCollisionsWith(mainCircle);

			if(collideNum > mainCircle.getRadius()){
				return -1;
			}else{
				return collideNum;
			}
		}
	}

	// Return 0 for no collision
	// return -1 if the other circle is bigger than the power up circle
	// return other circle radius if it is smaller than the powerup circle
	int checkCollisionForPowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			int collideNum = otherCircles.checkCollisionsWith(*it);
			if(collideNum > 0){
				if(collideNum > it->getRadius()){
					powerUpCircles.erase(it);
					return -1;
				}else{
					powerUpCircles.erase(it);
					return collideNum;
				}
			}
		}
		return 0;
	}

	// Returns 1 for collision
	// Returns 0 for no colision
	int checkCollisionForPowerUps(){
		if(mainCircle.inCar()){
			if(powerUps.checkCollisionsWith(mainCircle.getCar()) > 0){
				return 1;
			}
		}else{
			if(powerUps.checkCollisionsWith(mainCircle) > 0){
				return 1;
			}
		}

		return 0;
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

		for(auto pit = powerUpCircles.begin(); pit != powerUpCircles.end(); ++pit){
			if(needles.checkCollisionsWith(*pit, false) > 0){
				return 2;
			}
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
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(mainCircle.inCar()){
				if(squareFlowerCollision(*it, mainCircle.getCar())){
					buddyPowerUps.erase(it);
					return -1;
				}
			}else{
				// Check collision with main circle
				if(circleSquareCollision(mainCircle, *it)){
					buddyPowerUps.erase(it);
					return -1;
				}
			}
		}

		return 0;
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
		int collideNum;
		if(mainCircle.inCar()){
			collideNum = traps.checkCollisionsWith(mainCircle.getCar());
		}else{
			collideNum = traps.checkCollisionsWith(mainCircle);
		}

		if(collideNum > 0){
			mainCircle.activateTrap(collideNum);
			return -1;
		}

		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(mainCircle.inCar()){
				if(flowerFlowerCollision(mainCircle.getCar(), *it)){
					mainCircle.activateCar();
					circleCars.erase(it);
					return -1;
				}
			}else{
				// Check collision with main circle
				if(circleFlowerCollision(mainCircle, *it)){
					mainCircle.activateCar();
					circleCars.erase(it);
					return -1;
				}
			}
		}

		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForNukes(){
		if(mainCircle.inCar()){
			if(nukes.checkCollisionsWith(mainCircle.getCar()) > 0){
				return -1;
			}
		}else{
			if(nukes.checkCollisionsWith(mainCircle) > 0){
				return -1;
			}
		}

		return 0;
	}

	// 
	// Deleting Shapes
	// 
	void deleteAllPowerUpCircles(){
		powerUpCircles.clear();
	}

	void deleteAllBuddyPowerUps(){
		buddyPowerUps.clear();
	}

	void deleteBuddyCircle(){
		mainCircle.killBuddy();
	}

	void deleteAllCircleCars(){
		circleCars.clear();
	}

	// 
	// Shape changes
	// 

	// Main Circle
	void resetMainCirclePosition(){
		mainCircle.setPosition(olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2));
	}

	void resetMainCircleObjects(){
		mainCircle.inactivateObjects();
	}

	void growMainCircle(int amount){
		mainCircle.addRadius(amount);
		growBuddyCircle(amount);
	}

	void setMainCircleRadius(int radius){
		mainCircle.setRadius(radius);
	}

	// Main Circle Car
	void killMainCircleCar(){
		mainCircle.inactivateCar();
	}

	// Buddy Circle
	void resetBuddyCircle(){
		mainCircle.killBuddy();
	}

	void growBuddyCircle(int amount){
		mainCircle.growBuddy(amount);
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