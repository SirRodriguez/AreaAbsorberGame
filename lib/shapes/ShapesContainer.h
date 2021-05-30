#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "derivedShapes\Circle.h"
#include "derivedShapes\Triangle.h"
#include "..\utils.h"

#define square(x) ((x)*(x))

struct ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	int maxRadius;
	// Shapes
	Circle mainCircle;
	std::list<Circle> otherCircle;
	std::list<Triangle> powerUps;

	// Direction of where the power up circles will go
	enum direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	std::list<std::pair<direction, Circle>> powerUpCircles;


	void initialize(olc::PixelGameEngine& pge){
		otherCircle.clear();
		powerUps.clear();
		maxRadius = 50;
		pixelGameEngine = &pge;
		olc::vi2d mainPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		mainCircle = Circle(pge, mainPos, 10);
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
			it->second.clear();
		}
	}

	void hidePowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->clear();
		}
	}

	void hideAll(){
		hideCircles();
		hideMainCircle();
		hidePowerUps();
		hidePowerUpCircles();
	}

	void drawMainCircle(const olc::Pixel color){
		mainCircle.draw(color);
	}

	void drawCircles(const olc::Pixel color){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->draw(color);
		}
	}

	void drawPowerUps(const olc::Pixel color){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->draw(color);
		}
	}

	void drawPowerUpCircles(const olc::Pixel color){
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->second.draw(color);
		}
	}

	// 
	// List additions
	// 

	void addCircle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int radius = rand() % maxRadius;
		otherCircle.push_back(Circle(*pixelGameEngine, loc, radius));
	}

	void addPowerUp(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int height = 50;
		powerUps.push_back(Triangle(*pixelGameEngine, loc, height));
	}

	void addPowerUpCircles(){
		olc::vi2d pos = mainCircle.getPosition();
		powerUpCircles.push_back(std::make_pair(direction::UP, Circle(*pixelGameEngine, pos, mainCircle.getRadius())));
		powerUpCircles.push_back(std::make_pair(direction::DOWN, Circle(*pixelGameEngine, pos, mainCircle.getRadius())));
		powerUpCircles.push_back(std::make_pair(direction::LEFT, Circle(*pixelGameEngine, pos, mainCircle.getRadius())));
		powerUpCircles.push_back(std::make_pair(direction::RIGHT, Circle(*pixelGameEngine, pos, mainCircle.getRadius())));
	}

	// 
	// Moving Shapes
	// 

	void moveMainCircleUp(int pixels){
		if(mainCircle.belowTopOfScreen())
			mainCircle.movePosition(olc::vi2d(0, -pixels));
	}
	void moveMainCircleDown(int pixels){
		if(mainCircle.aboveBottomOfScreen())
			mainCircle.movePosition(olc::vi2d(0, pixels));
	}
	void moveMainCircleLeft(int pixels){
		if(mainCircle.rightOfLeftOfScreen())
			mainCircle.movePosition(olc::vi2d(-pixels, 0));
	}
	void moveMainCircleRight(int pixels){
		if(mainCircle.leftOfRightOfScreen())
			mainCircle.movePosition(olc::vi2d(pixels, 0));
	}

	void moveCircles(int pixels){
		for(auto it = otherCircle.begin(); it != otherCircle.end();){
			it->movePosition(olc::vi2d(0, pixels));
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
			it->movePosition(olc::vi2d(0, pixels));
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
			switch(it->first){
				case direction::UP:
					it->second.movePosition(olc::vi2d(0, -pixels));
					if(!it->second.belowTopOfScreen()){
						powerUpCircles.erase(it++);
					}else{
						++it;
					}
					break;
				case direction::DOWN:
					it->second.movePosition(olc::vi2d(0, pixels));
					if(!it->second.aboveBottomOfScreen()){
						powerUpCircles.erase(it++);
					}else{
						++it;
					}
					break;
				case direction::LEFT:
					it->second.movePosition(olc::vi2d(-pixels, 0));
					if(!it->second.rightOfLeftOfScreen()){
						powerUpCircles.erase(it++);
					}else{
						++it;
					}
					break;
				case direction::RIGHT:
					it->second.movePosition(olc::vi2d(pixels, 0));
					if(!it->second.leftOfRightOfScreen()){
						powerUpCircles.erase(it++);
					}else{
						++it;
					}
					break;
				default:
					++it;
					break;
			}
		}
	}

	void moveShapes(int pixels){
		moveCircles(pixels);
		movePowerUps(pixels);
		movePowerUpCircles(pixels);
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
				if(circleCircleCollision(*it, pit->second)){
					if(otherRadius > pit->second.getRadius()){
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

	// 
	// Shape changes
	// 

	void growMainCircle(int amount){
		mainCircle.addRadius(amount);
	}

	void setMainCircleRadius(int radius){
		mainCircle.setRadius(radius);
	}

	// 
	// Checks
	// 

	bool mainCircleTooBig(){
		return mainCircle.getRadius() >= 50;
	}
};

#endif