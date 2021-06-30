#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "../objects/mainCircle/MainCircle.h"
#include "../objects/OtherCircle.h"
#include "../objects/powerUp/PowerUp.h"
#include "../objects/powerUp/PowerUpCircle.h"
#include "../objects/Needle.h"
#include "../objects/BuddyPowerUp.h"
#include "../objects/Trap.h"
#include "../objects/CircleCar.h"
#include "../objects/Nuke.h"

#include "../utils.h"

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
	std::list<PowerUp> powerUps;
	std::list<CircleCar> circleCars;
	std::list<BuddyPowerUp> buddyPowerUps;
	std::list<PowerUpCircle> powerUpCircles;
	std::list<Nuke> nukes;

	// Enemies
	std::list<Needle> needles;
	std::list<Trap> traps;
	std::list<OtherCircle> otherCircle;

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

		// Make sure that the lists are cleared
		otherCircle.clear();
		powerUps.clear();
		powerUpCircles.clear();
		needles.clear();
		buddyPowerUps.clear();
		traps.clear();
	}

	void reset(){
		setMainCircleRadius(initialMainCircleSize);
		resetMainCircleObjects();

		deleteAllCircles();
		deleteAllPowerUps();
		deleteAllBuddyPowerUps();
		deleteAllPowerUpCircles();
		deleteAllNeedles();
		deleteAllTraps();
		deleteAllCircleCars();
		deleteAllNukes();
	}

	void clearForNextLevel(){
		setMainCircleRadius(initialMainCircleSize);
		deleteAllCircles();
		deleteAllNeedles();
		deleteAllTraps();
	}

	// 
	// Drawing
	// 

	void hideMainCircle(){
		mainCircle.clear();
	}

	void hideCircles(){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->clear();
		}
	}

	void hidePowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->clear();
		}
	}

	void hidePowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->clear();
		}
	}

	void hideNeedles(){
		for(auto it = needles.begin(); it != needles.end(); ++it){
			it->clear();
		}
	}

	void hideBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->clear();
		}
	}

	void hideTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->clear();
		}
	}

	void hideCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->clear();
		}
	}

	void hideNukes(){
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			it->clear();
		}
	}

	void hideAll(){
		hideCircles();
		hideMainCircle();
		hidePowerUps();
		hidePowerUpCircles();
		hideNeedles();
		hideBuddyPowerUps();
		hideTraps();
		hideCircleCars();
		hideNukes();
	}

	void drawMainCircle(){
		mainCircle.draw();
	}

	void drawCircles(){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->draw();
		}
	}

	void drawPowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->draw();
		}
	}

	void drawPowerUpCircles(){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->draw();
		}
	}

	void drawNeedles(){
		for(auto it = needles.begin(); it != needles.end(); ++it){
			it->draw();
		}
	}

	void drawBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->draw();
		}
	}

	void drawTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->draw();
		}
	}

	void drawCircleCars(){
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->draw();
		}
	}

	void drawNukes(){
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			it->draw();
		}
	}

	void drawAllShapes(){
		drawMainCircle();
		drawCircles();
		drawPowerUps();
		drawPowerUpCircles();
		drawNeedles();
		drawBuddyPowerUps();
		drawTraps();
		drawCircleCars();
		drawNukes();
	}

	// 
	// List additions
	// 

	// Direction code tells the direction where the circle is comming from on the screen
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
	void addCircle(uint8_t dirFromCode){
		auto makeCircle = [&](olc::vi2d _loc, int dirCode){
			otherCircle.push_back(OtherCircle(*pixelGameEngine, _loc, otherCircleSpeed, otherCircleColor, rand() % otherCircleMaxRadius, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeCircle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeCircle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeCircle(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeCircle(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeCircle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeCircle(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeCircle(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeCircle(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeCircle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeCircle(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeCircle(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeCircle(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
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
	void addPowerUp(uint8_t dirFromCode){
		auto makePowerUp = [&](olc::vi2d _loc, int dirCode){
			powerUps.push_back(PowerUp(*pixelGameEngine, _loc, powerUpSpeed, powerUpColor, powerUpHeight, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makePowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makePowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makePowerUp(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makePowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makePowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makePowerUp(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makePowerUp(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makePowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makePowerUp(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makePowerUp(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makePowerUp(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makePowerUp(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
			}
		}
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
		auto makeNeedle = [&](olc::vi2d _loc, int dirCode){
			needles.push_back(Needle(*pixelGameEngine, _loc, needleSpeed, needleColor, rand() % maxNeedleLength, rand() % maxNeedleLength, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeNeedle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeNeedle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeNeedle(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeNeedle(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeNeedle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeNeedle(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeNeedle(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeNeedle(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeNeedle(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeNeedle(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeNeedle(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeNeedle(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
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
		auto makeTrap = [&](olc::vi2d _loc, int dirCode){
			traps.push_back(Trap(*pixelGameEngine, _loc, trapSpeed, trapColor, trapLength, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeTrap(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeTrap(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeTrap(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeTrap(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeTrap(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeTrap(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeTrap(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeTrap(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeTrap(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeTrap(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeTrap(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeTrap(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
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
		auto makeNuke = [&](olc::vi2d _loc, int dirCode){
			// const uint8_t circleCarNumWheels = 4;
			// const double degOffset = 45.0;
			nukes.push_back(Nuke(*pixelGameEngine, _loc, nukeSpeed, nukeColor, nukePedalColor, nukeRadius, dirCode));
		};

		if(dirFromCode & 0x01){ // FROM TOP
			makeNuke(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			makeNuke(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			makeNuke(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			makeNuke(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				makeNuke(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				makeNuke(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				makeNuke(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				makeNuke(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				makeNuke(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				makeNuke(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				makeNuke(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				makeNuke(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
			}
		}

	}

	// 
	// Moving Shapes
	// 
	void moveMainCircle(){
		mainCircle.move();
	}

	void moveCircles(){
		for(auto it = otherCircle.begin(); it != otherCircle.end();){
			it->move();
			if(it->outOfBounds()){
				otherCircle.erase(it++);
			}else{
				++it;
			}
		}
	}

	void movePowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end();){
			it->move();
			if(it->outOfBounds()){
				powerUps.erase(it++);
			}else{
				++it;
			}
		}
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

	void moveNeedles(){
		for(auto it = needles.begin(); it != needles.end();){
			it->move();
			if(it->outOfBounds()){
				needles.erase(it++);
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

	void moveTraps(){
		for(auto it = traps.begin(); it != traps.end();){
			it->move();
			if(it->outOfBounds()){
				traps.erase(it++);
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

	void moveNukes(){
		for(auto it = nukes.begin(); it != nukes.end();){
			it->move();
			if(it->outOfBounds()){
				nukes.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveAllShapes(){
		moveMainCircle();
		moveCircles();
		movePowerUps();
		movePowerUpCircles();
		moveNeedles();
		moveBuddyPowerUps();
		moveTraps();
		moveCircleCars();
		moveNukes();
	}

	// 
	// Deleting Shapes
	// 

	void deleteAllCircles(){
		otherCircle.clear();
	}

	void deleteAllPowerUps(){
		powerUps.clear();
	}

	void deleteAllPowerUpCircles(){
		powerUpCircles.clear();
	}

	void deleteAllNeedles(){
		needles.clear();
	}

	void deleteAllBuddyPowerUps(){
		buddyPowerUps.clear();
	}

	void deleteBuddyCircle(){
		mainCircle.killBuddy();
	}

	void deleteAllTraps(){
		traps.clear();
	}

	void deleteAllCircleCars(){
		circleCars.clear();
	}

	void deleteAllNukes(){
		nukes.clear();
	}

	// 
	// Collision detection
	// 

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollisionForCircle(){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			int otherRadius = it->getRadius();
			// If in car
			if(mainCircle.inCar()){
				if(circleFlowerCollision(*it, mainCircle.getCar())){
					mainCircle.hitCar(otherRadius);
					otherCircle.erase(it);
					return otherRadius;
				}

			// If not in car
			}else if(circleCircleCollision(mainCircle, *it)){
				if(otherRadius > mainCircle.getRadius()){
					return -1;
				}else{
					otherCircle.erase(it);
					return otherRadius;
				}
			}
		}

		return 0;
	}

	// Return 0 for no collision
	// return -1 if the other circle is bigger than the power up circle
	// return other circle radius if it is smaller than the powerup circle
	int checkCollisionForPowerUpCircles(){
		int otherRadius;
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			otherRadius = it->getRadius();
			for(auto pit = powerUpCircles.begin(); pit != powerUpCircles.end(); ++pit){
				if(circleCircleCollision(*it, *pit)){
					if(otherRadius > pit->getRadius()){
						otherCircle.erase(it);
						powerUpCircles.erase(pit);
						return -1;
					}else{
						powerUpCircles.erase(pit);
						otherCircle.erase(it);
						return otherRadius;
					}
				}
			}
		}

		return 0;
	}

	// Returns 1 for collision
	// Returns 0 for no colision
	int checkCollisionForPowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			// Check if main circle has car
			if(mainCircle.inCar()){
				if(triangleFlowerCollision(*it, mainCircle.getCar())){
					powerUps.erase(it);
					return 1;
				}
			}else{
				if(circleTriangleCollision(mainCircle, *it)){
					powerUps.erase(it);
					return 1;
				}				
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
		for(auto it = needles.begin(); it != needles.end(); ++it){
			// Check collision with circle car
			if(mainCircle.inCar()){
				if(lineFlowerCollision(*it, mainCircle.getCar())){
					needles.erase(it); // Delete needle with it
					return -4;
				}
			}

			// Check collision for trapped box
			if(mainCircle.isTrapped()){
				if(lineSquareCollision(*it, mainCircle.getTrapSquare())){
					return -3;
				}
			}

			// Check collision with main circle
			if(circleLineCollision(mainCircle, *it)){
				return -1;
			}

			// Check collision with other circles
			for(auto oit = otherCircle.begin(); oit != otherCircle.end(); ++oit){
				if(circleLineCollision(*oit, *it)){
					otherCircle.erase(oit);
					return 1;
				}
			}

			// check collision with powerUpCircles
			for(auto pit = powerUpCircles.begin(); pit != powerUpCircles.end(); ++pit){
				if(circleLineCollision(*pit, *it)){
					powerUpCircles.erase(pit);
					return 2;
				}
			}

			// Check collision with buddy circle
			if(circleLineCollision(mainCircle.getBuddy(), *it)){
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
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				// Check collision with other circles
				if(circleCircleCollision(*it, mainCircle.getBuddy())){
					if(mainCircle.getBuddyRadius() > it->getRadius()){
						otherCircle.erase(it);
						return it->getRadius();
					}else{
						otherCircle.erase(it);
						return -1;
					}
				}
			}
		}

		return 0;
	}

	// Return 0 for no collisions
	// Return -1 for collision
	int checkCollisionForTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(mainCircle.inCar()){
				if(squareFlowerCollision(*it, mainCircle.getCar())){
					// Activate trap for main circle
					mainCircle.activateTrap(it->getDirectionCode());
					traps.erase(it);
					return -1;
				}
			}else{
				// Check collision with main circle
				if(circleSquareCollision(mainCircle, *it)){
					// Activate trap for main circle
					mainCircle.activateTrap(it->getDirectionCode());
					traps.erase(it);
					return -1;
				}
			}
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
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(mainCircle.inCar()){
				if(flowerFlowerCollision(mainCircle.getCar(), *it)){
					nukes.erase(it);
					return -1;
				}
			}else{
				// Check collision with the circle itself
				if(circleFlowerCollision(mainCircle, *it)){
					nukes.erase(it);
					return -1;
				}
			}
		}

		return 0;
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
		needles.clear();
		traps.clear();
		otherCircle.clear();
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