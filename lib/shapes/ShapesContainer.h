#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "derivedShapes\Circle.h"
#include "derivedShapes\Triangle.h"

#define square(x) ((x)*(x))

// int square(int x){ return x*x; }


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
	// int checkCollisionForCircle(const olc::vi2d& pos, const int& radius){
	int checkCollisionForCircle(){
		const olc::vi2d pos = mainCircle.getPosition();
		const int radius = mainCircle.getRadius();

		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			// Check the collision of the main circle
			// Get the distances
			olc::vi2d otherPos = it->getPosition();
			int32_t x = otherPos.x;
			int32_t y = otherPos.y;

			// int distanceSqr = (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y);
			int distanceSqr = square(pos.x - x) + square(pos.y - y);


			// Check if distance is less or equal to the two radius combined
			int otherRadius = it->getRadius();
			if(distanceSqr <= square(otherRadius + radius)){
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

	// Return 0 for no collision
	// return -1 if the other circle is bigger than the power up circle
	// return other circle radius if it is smaller than the powerup circle
	int checkCollisionForPowerUpCircles(){
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			olc::vi2d otherPos = it->getPosition();
			int other_x = otherPos.x;
			int other_y = otherPos.y;
			int otherRadius = it->getRadius();

			for(auto pit = powerUpCircles.begin(); pit != powerUpCircles.end(); ++pit){
				olc::vi2d pwrPos = pit->second.getPosition();
				int pwr_x = pwrPos.x;
				int pwr_y = pwrPos.y;
				int pwrRadius = pit->second.getRadius();

				int distanceSqr = square(other_x - pwr_x) + square(other_y - pwr_y);
				if(distanceSqr <= square(otherRadius + pwrRadius)){
					// If the other circle is bigger than the power circle
					if(otherRadius > pwrRadius){
						// delete the power up circle
						powerUpCircles.erase(pit);
						return -1;
					}else{
						// delete power up circle and the other circle
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
		const olc::vi2d pos = mainCircle.getPosition();
		const int radius = mainCircle.getRadius();
		int radiusSqr = radius * radius;

		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			olc::vi2d tp = it->topPoint();
			olc::vi2d blp = it->botLeftPoint();
			olc::vi2d brp = it->botRightPoint();

			// 
			// Test 1: Vertex within the circle
			// 
			// Top point
			int c1x = pos.x - tp.x;
			int c1y = pos.y - tp.y;
			int c1sqr = c1x * c1x + c1y * c1y - radiusSqr;
			if(c1sqr <= 0){
				powerUps.erase(it);
				return 1;
			}
			// bottom left point
			int c2x = pos.x - blp.x;
			int c2y = pos.y - blp.y;
			int c2sqr = c2x * c2x + c2y * c2y - radiusSqr;
			if(c2sqr <= 0){
				powerUps.erase(it);
				return 1;
			}
			// bottom right point
			int c3x = pos.x - brp.x;
			int c3y = pos.y - brp.y;
			int c3sqr = c3x * c3x + c3y * c3y - radiusSqr;
			if(c3sqr <= 0){
				powerUps.erase(it);
				return 1;
			}

			// 
			// Test 2: Circle center within the triangle
			// 
			// Get edges
			int e1x = brp.x - tp.x;
			int e1y = brp.y - tp.y;

			int e2x = blp.x - brp.x;
			int e2y = blp.y - brp.y;

			int e3x = tp.x - blp.x;
			int e3y = tp.y - blp.y;

			if(e1y*c1x >= e1x*c1y && e2y*c2x >= e2x*c2y && e3y*c3x >= e3x*c3y){
				powerUps.erase(it);
				return 1;
			}

			// 
			// Test 3: Circle intersects edge
			// 
			// First edge
			int k = c1x*e1x + c1y*e1y;
			if(k > 0){
				int len = e1x*e1x + e1y*e1y;
				if(k < len){
					if(c1sqr * len <= k*k){
						powerUps.erase(it);
						return 1;
					}
				}
			}
			// Second edge
			k = c2x*e2x + c2y*e2y;
			if(k > 0){
				int len = e2x*e2x + e2y*e2y;
				if(k < len){
					if(c2sqr * len <= k*k){
						powerUps.erase(it);
						return 1;
					}
				}
			}
			// Third edge
			k = c3x*e3x + c3y*e3y;
			if(k > 0){
				int len = e3x*e3x + e3y*e3y;
				if(k < len){
					if(c3sqr * len <= k*k){
						powerUps.erase(it);
						return 1;
					}
				}
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