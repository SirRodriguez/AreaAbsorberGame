#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

// #include "..\shapes\derivedShapes\Circle.h"
// #include "..\shapes\derivedShapes\Triangle.h"
// #include "..\shapes\derivedShapes\Line.h"
// #include "..\shapes\derivedShapes\Square.h"
// #include "..\shapes\derivedShapes\BuddyCircle.h"

#include "..\objects\MainCircle.h"
#include "..\objects\OtherCircle.h"
#include "..\objects\PowerUp.h"
#include "..\objects\PowerUpCircle.h"
#include "..\objects\Needle.h"
#include "..\objects\BuddyPowerUp.h"
#include "..\objects\BuddyCircle.h"

// #include "..\shapes\derivedShapes\Box.h"
#include "..\utils.h"

class ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	int maxRadius;
	int maxLength;
	int initialMainCircleSize = 10;

	// Shapes
	// Circle mainCircle;
	MainCircle mainCircle;
	// std::list<Circle> otherCircle;
	std::list<OtherCircle> otherCircle;
	// std::list<Triangle> powerUps;
	std::list<PowerUp> powerUps;
	// std::list<Line> needles;
	std::list<Needle> needles;
	// std::list<Box> trapBoxes;

	// For the buddy shapes power ups
	// std::list<Square> buddyPowerUps;
	std::list<BuddyPowerUp> buddyPowerUps;
	BuddyCircle buddyCircle;

	// Direction of where the power up circles will go
	enum direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UPLEFT,
		UPRIGHT,
		DOWNLEFT,
		DOWNRIGHT
	};
	// std::list<std::pair<direction, Circle>> powerUpCircles;
	std::list<PowerUpCircle> powerUpCircles;


public:
	void initialize(olc::PixelGameEngine& pge){
		otherCircle.clear();
		powerUps.clear();
		powerUpCircles.clear();
		needles.clear();
		buddyPowerUps.clear();
		// trapBoxes.clear();

		pixelGameEngine = &pge;
		olc::vi2d mainPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		mainCircle = MainCircle(pge, mainPos, initialMainCircleSize);

		buddyCircle = BuddyCircle(pge);

		maxRadius = 50;
		maxLength = 50;
	}

	void reset(){
		setMainCircleRadius(initialMainCircleSize);
		resetMainCirclePosition();
		deleteAllCircles();
		deleteAllPowerUpCircles();
		deleteAllNeedles();
		// deleteAllTrapBoxes();
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

	// void hideTrapBoxes(){
	// 	for(auto it = trapBoxes.begin(); it != trapBoxes.end(); ++it){
	// 		it->clear();
	// 	}
	// }

	void hideAll(){
		hideCircles();
		hideMainCircle();
		hidePowerUps();
		hidePowerUpCircles();
		hideNeedles();
		hideBuddyPowerUps();
		hideBuddyCircle();
		// hideTrapBoxes();
	}

	void drawMainCircle(const olc::Pixel& color){
		mainCircle.draw(color);
	}

	void drawCircles(const olc::Pixel& color){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->draw(color);
		}
	}

	void drawPowerUps(const olc::Pixel& color){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->draw(color);
		}
	}

	void drawPowerUpCircles(const olc::Pixel& color){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->draw(color);
		}
	}

	void drawNeedles(const olc::Pixel& color){
		for(auto it = needles.begin(); it != needles.end(); ++it){
			it->draw(color);
		}
	}

	void drawBuddyPowerUps(const olc::Pixel& color){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->draw(color);
		}
	}

	void drawBuddyCircle(const olc::Pixel& color){
		buddyCircle.draw(color);
	}

	// void drawTrapBoxes(const olc::Pixel& color){
	// 	for(auto it = trapBoxes.begin(); it != trapBoxes.end(); ++it){
	// 		it->draw(color);
	// 	}
	// }

	// 
	// List additions
	// 

	void addCircle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int radius = rand() % maxRadius;
		otherCircle.push_back(OtherCircle(*pixelGameEngine, loc, radius));
	}

	void addPowerUp(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int height = 50;
		powerUps.push_back(PowerUp(*pixelGameEngine, loc, height));
	}

	void addPowerUpCircles(){
		olc::vi2d pos = mainCircle.getPosition();
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 0));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 1));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 2));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 3));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 4));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 5));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 6));
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, pos, mainCircle.getRadius(), 7));
	}

	void addNeedle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int dx = rand() % maxLength;
		int dy = rand() % maxLength;
		needles.push_back(Needle(*pixelGameEngine, loc, dx, dy));
	}

	void addBuddyPowerUp(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int length = 40;
		buddyPowerUps.push_back(BuddyPowerUp(*pixelGameEngine, loc, length));
	}

	// void addTrapBox(){
	// 	olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
	// 	int radius = rand() % maxRadius;
	// 	trapBoxes.push_back(Circle(*pixelGameEngine, loc, radius));
	// }

	// 
	// Moving Shapes
	// 

	// void moveMainCircleUp(int pixels){
	// 	if(mainCircle.belowTopOfScreen())
	// 		mainCircle.movePosition(olc::vi2d(0, -pixels));
	// }
	// void moveMainCircleDown(int pixels){
	// 	if(mainCircle.aboveBottomOfScreen())
	// 		mainCircle.movePosition(olc::vi2d(0, pixels));
	// }
	// void moveMainCircleLeft(int pixels){
	// 	if(mainCircle.rightOfLeftOfScreen())
	// 		mainCircle.movePosition(olc::vi2d(-pixels, 0));
	// }
	// void moveMainCircleRight(int pixels){
	// 	if(mainCircle.leftOfRightOfScreen())
	// 		mainCircle.movePosition(olc::vi2d(pixels, 0));
	// }
	void moveMainCircle(int pixels){
		mainCircle.move(pixels);
	}

	void moveCircles(int pixels){
		for(auto it = otherCircle.begin(); it != otherCircle.end();){
			// it->movePosition(olc::vi2d(0, pixels));
			it->move(pixels);
			// if it reaches the bottom, delete it
			if(!it->aboveBottomOfScreen()){
				otherCircle.erase(it++);
			}else{
				++it;
			}
		}
	}

	void movePowerUps(int pixels){
		for(auto it = powerUps.begin(); it != powerUps.end();){
			// it->movePosition(olc::vi2d(0, pixels));
			it->move(pixels);
			// if it reaches the bottom, delete it
			if(!it->aboveBottomOfScreen()){
				powerUps.erase(it++);
			}else{
				++it;
			}
		}
	}

	void movePowerUpCircles(int pixels){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end();){
			++it;
			// TODO: Change
			// switch(it->first){
			// 	case direction::UP:
			// 		it->second.movePosition(olc::vi2d(0, -pixels));
			// 		if(!it->second.belowTopOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::DOWN:
			// 		it->second.movePosition(olc::vi2d(0, pixels));
			// 		if(!it->second.aboveBottomOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::LEFT:
			// 		it->second.movePosition(olc::vi2d(-pixels, 0));
			// 		if(!it->second.rightOfLeftOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::RIGHT:
			// 		it->second.movePosition(olc::vi2d(pixels, 0));
			// 		if(!it->second.leftOfRightOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::UPRIGHT:
			// 		it->second.movePosition(olc::vi2d(pixels, -pixels));
			// 		if(!it->second.leftOfRightOfScreen() || !it->second.belowTopOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::UPLEFT:
			// 		it->second.movePosition(olc::vi2d(-pixels, -pixels));
			// 		if(!it->second.belowTopOfScreen() || !it->second.rightOfLeftOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::DOWNLEFT:
			// 		it->second.movePosition(olc::vi2d(-pixels, pixels));
			// 		if(!it->second.rightOfLeftOfScreen() || !it->second.aboveBottomOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	case direction::DOWNRIGHT:
			// 		it->second.movePosition(olc::vi2d(pixels, pixels));
			// 		if(!it->second.aboveBottomOfScreen() || !it->second.leftOfRightOfScreen()){
			// 			powerUpCircles.erase(it++);
			// 		}else{
			// 			++it;
			// 		}
			// 		break;
			// 	default:
			// 		++it;
			// 		break;
			// }
		}
	}

	void moveNeedles(int pixels){
		for(auto it = needles.begin(); it != needles.end();){
			// it->movePosition(olc::vi2d(0, pixels));
			it->move(pixels);
			// if it reaches the bottom, delete it
			if(!it->aboveBottomOfScreen()){
				needles.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveBuddyPowerUps(int pixels){
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end();){
			// it->movePosition(olc::vi2d(0, pixels));
			it->move(pixels);
			// if it reaches the bottom, delete it
			if(!it->aboveBottomOfScreen()){
				buddyPowerUps.erase(it++);
			}else{
				++it;
			}
		}
	}

	void moveBuddyCircle(int pixels){
		buddyCircle.moveToCircle(mainCircle, pixels);
	}

	// void moveTrapBoxes(int pixels){
	// 	trapBoxes
	// }

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

	// 
	// Shape changes
	// 

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