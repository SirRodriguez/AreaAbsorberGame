#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "derivedShapes\Circle.h"
#include "derivedShapes\Triangle.h"

struct ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	Circle mainCircle;
	std::list<Circle> otherCircle;
	std::list<Triangle> powerUps;
	int maxRadius;

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

	void hideAll(){
		hideCircles();
		hideMainCircle();
	}

	void drawMainCircle(const olc::Pixel color){
		mainCircle.draw(color);
	}

	void drawCircles(const olc::Pixel color){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->draw(color);
		}
	}

	void addCircle(){
		olc::vi2d loc = olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0);
		int radius = rand() % maxRadius;
		otherCircle.push_back(Circle(*pixelGameEngine, loc, radius));
	}

	// 
	// Moving Shapes
	// 

	void moveMainCircleUp(int pixels){
		mainCircle.movePosition(olc::vi2d(0, -pixels));
	}
	void moveMainCircleDown(int pixels){
		mainCircle.movePosition(olc::vi2d(0, pixels));
	}
	void moveMainCircleLeft(int pixels){
		mainCircle.movePosition(olc::vi2d(-pixels, 0));
	}
	void moveMainCircleRight(int pixels){
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

	void moveShapes(int pixels){
		moveCircles(pixels);
		movePowerUps(pixels);
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
	// int checkCollisionForCircle(const olc::vi2d& pos, const int& radius){
	int checkCollisionForCircle(){
		const olc::vi2d pos = mainCircle.getPosition();
		const int radius = mainCircle.getRadius();

		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			// Get the distances
			olc::vi2d otherPos = it->getPosition();
			int32_t x = otherPos.x;
			int32_t y = otherPos.y;
			double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) );

			// Check if distance is less or equal to the two radius combined
			int otherRadius = it->getRadius();
			if(distance <= otherRadius + radius){
				// if the other circle is bigger
				if(otherRadius > radius){
					return -1;
				// else if the distance is less than or equal
				}else{
					otherCircle.erase(it);
					return otherRadius;
				}
			}
		}

		return 0;
	}

	int checkCollisionForPowerUps(const olc::vi2d& pos, const int& radius){
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