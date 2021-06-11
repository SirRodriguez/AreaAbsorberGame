#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "..\objects\MainCircle.h"
#include "..\objects\OtherCircle.h"
#include "..\objects\PowerUp.h"
#include "..\objects\PowerUpCircle.h"
#include "..\objects\Needle.h"
#include "..\objects\BuddyPowerUp.h"
#include "..\objects\BuddyCircle.h"
#include "..\objects\Trap.h"

#include "..\utils.h"

// Colors
const olc::Pixel mainCircleColor = olc::BLACK;
const olc::Pixel otherCircleColor = olc::RED;
const olc::Pixel powerUpColor = olc::GREEN;
const olc::Pixel powerUpCircleColor = olc::GREY;
const olc::Pixel needleColor = olc::BLACK;
const olc::Pixel buddyPowerUpColor = olc::YELLOW;
const olc::Pixel buddyCircleColor = olc::DARK_GREY;
const olc::Pixel trapColor = olc::BLUE;

// Speeds
const uint8_t otherCircleSpeed = 4;
const uint8_t powerUpSpeed = 2;
const uint8_t powerUpCircleSpeed = 5;
const uint8_t needleSpeed = 6;
const uint8_t buddyPowerUpSpeed = 2;
const uint8_t buddyCircleSpeed = 2;
const uint8_t mainCircleSpeed = 5;
const uint8_t trapSpeed = 4;

class ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	int maxRadius = 50;
	int maxLength = 50;
	int initialMainCircleSize = 10;

	// Shapes
	MainCircle mainCircle;
	std::list<OtherCircle> otherCircle;
	std::list<PowerUp> powerUps;
	std::list<Needle> needles;
	std::list<Trap> traps;

	// For the buddy shapes power ups
	std::list<BuddyPowerUp> buddyPowerUps;
	BuddyCircle buddyCircle;

	std::list<PowerUpCircle> powerUpCircles;

public:
	ShapesContainer()
	: pixelGameEngine(nullptr){}
	ShapesContainer(olc::PixelGameEngine& pge)
	: pixelGameEngine(&pge){
		olc::vi2d centerPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);

		// Initialize the main circle and buddy circle
		mainCircle = MainCircle(pge, centerPos, mainCircleSpeed, mainCircleColor, initialMainCircleSize, 0);
		buddyCircle = BuddyCircle(pge, centerPos, buddyCircleSpeed, buddyCircleColor, 0, 0);

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
		deleteAllCircles();
		deleteAllPowerUpCircles();
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

	void hideBuddyCircle(){
		buddyCircle.clear();
	}

	void hideTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
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
		hideBuddyCircle();
		hideTraps();
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

	void drawBuddyCircle(){
		buddyCircle.draw();
	}

	void drawTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
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
		drawBuddyCircle();
		drawTraps();
	}

	// 
	// List additions
	// 

	void addCircle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int radius = rand() % maxRadius;
		otherCircle.push_back(OtherCircle(*pixelGameEngine, loc, otherCircleSpeed, otherCircleColor, radius));
	}

	void addPowerUp(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int height = 50;
		powerUps.push_back(PowerUp(*pixelGameEngine, loc, powerUpSpeed, powerUpColor, height));
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

	void addNeedle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int dx = rand() % maxLength;
		int dy = rand() % maxLength;
		needles.push_back(Needle(*pixelGameEngine, loc, needleSpeed, needleColor, dx, dy));
	}

	void addBuddyPowerUp(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int length = 40;
		buddyPowerUps.push_back(BuddyPowerUp(*pixelGameEngine, loc, buddyCircleSpeed, buddyPowerUpColor, length));
	}

	void addTrap(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int length = 40;
		traps.push_back(Trap(*pixelGameEngine, loc, trapSpeed, trapColor, length));
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

	void moveBuddyCircle(){
		buddyCircle.move(mainCircle);
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

	void moveAllShapes(){
		moveMainCircle();
		moveCircles();
		movePowerUps();
		movePowerUpCircles();
		moveNeedles();
		moveBuddyPowerUps();
		moveBuddyCircle();
		moveTraps();
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
		buddyCircle.kill();
	}

	void deleteAllTraps(){
		traps.clear();
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
			if(circleCircleCollision(mainCircle, *it)){
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
			if(circleTriangleCollision(mainCircle, *it)){
				powerUps.erase(it);
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
	int checkCollisionForNeedles(){
		for(auto it = needles.begin(); it != needles.end(); ++it){
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
			if(circleLineCollision(buddyCircle, *it)){
				return -2;
			}
		}
		return 0;
	}

	// Returns 0 for no collision
	// Returns -1 for collision with main circle
	int checkCollisionForBuddyPowerUps(){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			// Check collision with main circle
			if(circleSquareCollision(mainCircle, *it)){
				buddyPowerUps.erase(it);
				return -1;
			}
		}

		return 0;
	}

	// Return 0 for no collision
	// Return negative number for Collision with other circle thats bigger
	// Return positive number for collision with other circle thats smaller
	int checkCollisionForBuddyCircle(){
		if(buddyCircle.alive()){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				// Check collision with other circles
				if(circleCircleCollision(*it, buddyCircle)){
					if(buddyCircle.getRadius() > it->getRadius()){
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

	int checkCollisionForTraps(){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			// Check collision with main circle
			if(circleSquareCollision(mainCircle, *it)){
				traps.erase(it);
				return -1;
			}
		}

		return 0;
	}

	// 
	// Shape changes
	// 

	void resetBuddyCircle(){
		buddyCircle.kill();
	}

	void resetMainCirclePosition(){
		mainCircle.setPosition(olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2));
	}

	void growMainCircle(int amount){
		mainCircle.addRadius(amount);
		growBuddyCircle(amount);
	}

	void setMainCircleRadius(int radius){
		mainCircle.setRadius(radius);
	}

	void growBuddyCircle(int amount){
		buddyCircle.grow(amount);
	}

	void addLifeToBuddyCircle(int amount){
		buddyCircle.addLife(amount);
	}

	void subtractLifeToBuddyCircle(int amount){
		buddyCircle.subtractLife(amount);
	}

	// 
	// Checks
	// 

	bool mainCircleTooBig(){
		return mainCircle.getRadius() >= 50;
	}
};

#endif