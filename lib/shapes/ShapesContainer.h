#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "derivedShapes\Circle.h"
#include "derivedShapes\Triangle.h"

// 
// Utility functions
// 

// Checks if there is a collision with a circle and a line
// Line equation: ax + by + c = 0
// Circle: center = (x, y); radius = radius;
// return 0 if no touch
// return 1 if touches
// return 2 if intersects
int colisionWithCircleAndLine(int a, int b, int c, int x, int y, int radius){
	// Finding the distance of line from center.
    int dist = (abs(a * x + b * y + c)) / sqrt(a * a + b * b);

    // Circle touches the line
    if(radius == dist){
    	return 1;
    // Circle intersects the line
    }else if(radius > dist){
    	return 2;
    // Circle is outside the line
    }else{
    	return 0;
    }
}

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

	void hidePowerUps(){
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->clear();
		}
	}

	void hideAll(){
		hideCircles();
		hideMainCircle();
		hidePowerUps();
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
			double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) ); // TODO: Optimize

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
				return 1;
			}
			// bottom left point
			int c2x = pos.x - blp.x;
			int c2y = pos.y - blp.y;
			int c2sqr = c2x * c2x + c2y * c2y - radiusSqr;
			if(c2sqr <= 0){
				return 1;
			}
			// bottom right point
			int c3x = pos.x - brp.x;
			int c3y = pos.y - brp.y;
			int c3sqr = c3x * c3x + c3y * c3y - radiusSqr;
			if(c3sqr <= 0){
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

			if(e1y*c1x <= e1x*c1y && e2y*c2x <= e2x*c2y && e3y*c3x <= e3x*c3y){
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