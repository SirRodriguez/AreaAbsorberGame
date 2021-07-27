#ifndef CIRCLECARLIST_H
#define CIRCLECARLIST_H

#include "../ShapeList.h"
#include "../../objects/CircleCar.h"

#define POWERUPCODE 2

class CircleCarList: public ShapeList{
protected:
	std::list<CircleCar> circleCars;
	olc::Pixel default_color;
	olc::Pixel default_wheel_color;
	uint8_t default_speed;
	uint8_t default_radius;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		circleCars.push_back(CircleCar(*pixelGameEngine, _loc, default_speed, default_color, default_wheel_color, default_radius, dirCode));
	}

public:
	CircleCarList()
	: ShapeList(POWERUPCODE){}
	CircleCarList(olc::PixelGameEngine& pge, olc::Pixel _color, olc::Pixel _wheel_color, uint8_t _speed, uint8_t _radius)
	: ShapeList(pge, POWERUPCODE), default_color(_color), default_wheel_color(_wheel_color), default_speed(_speed), default_radius(_radius){}

	virtual void deleteAll() override {
		circleCars.clear();
	}

	virtual void hideAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end();){
			it->move();
			if(it->outOfBounds()){
				circleCars.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(c, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(*it, f)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(l, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(s, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(t, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(*it, mc)){
				int radius = it->getRadius();
				if(removeOnCollision) circleCars.erase(it);
				return radius;
			}
		}

		return 0;
	}
};

#endif