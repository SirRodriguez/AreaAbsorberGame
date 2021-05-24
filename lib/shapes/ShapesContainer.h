#ifndef SHAPESCONTAINER
#define SHAPESCONTAINER

#include "derivedShapes\Circle.h"

struct ShapesContainer{
	olc::PixelGameEngine* pixelGameEngine;
	int id;
	std::list<Circle> otherCircle;
	int maxRadius;

	void initialize(olc::PixelGameEngine& pge){
		id = 0;
		otherCircle.clear();
		maxRadius = 50;
		pixelGameEngine = &pge;
	}

	// Iterators
	std::list<Circle>::iterator begin(){
		return otherCircle.begin();
	}
	std::list<Circle>::iterator end(){
		return otherCircle.end();
	}

	void addShape(int32_t screenWidth){
		olc::vi2d loc = olc::vi2d(rand() % screenWidth, 0);
		int radius = rand() % maxRadius;
		otherCircle.push_back(Circle(*pixelGameEngine, loc, radius));
		++id;
	}

	void moveShapes(int32_t screenHeight, int pixels){
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

	void deleteAllShapes(){
		otherCircle.clear();
	}

	// return 0 if no collision
	// return -1 if other circle is bigger
	// return any positive number means that the circle was smaller and thats the size
	int checkCollision2(const olc::vi2d& pos, const int& radius){
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
};

#endif