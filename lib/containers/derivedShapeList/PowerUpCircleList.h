#ifndef POWERCIRCLELIST_H
#define POWERCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/powerUp/PowerUpCircle.h"
#include "../../Direction.h"

#define BUDDYCODE 1

class PowerUpCircleList: public ShapeList{
protected:
	std::list<PowerUpCircle> powerUpCircles;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_size;

	virtual void make(olc::vi2d _loc, Direction dirCode, uint8_t _size){
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, _loc, default_speed, default_color, _size, dirCode));
	}

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, _loc, default_speed, default_color, default_size, dirCode));
	}

public:
	PowerUpCircleList()
	: ShapeList(BUDDYCODE){}
	PowerUpCircleList(olc::PixelGameEngine& pge, olc::Pixel _color, uint8_t _speed, uint8_t _size)
	: ShapeList(pge, BUDDYCODE), default_color(_color), default_speed(_speed), default_size(_size){}

	virtual void add(olc::vi2d pos) {
		make(pos, Direction::UP);
		make(pos, Direction::DOWN);
		make(pos, Direction::LEFT);
		make(pos, Direction::RIGHT);
		make(pos, Direction::UPLEFT);
		make(pos, Direction::UPRIGHT);
		make(pos, Direction::DOWNLEFT);
		make(pos, Direction::DOWNRIGHT);
	}

	virtual void add(olc::vi2d pos, uint8_t _size){
		make(pos, Direction::UP, _size);
		make(pos, Direction::DOWN, _size);
		make(pos, Direction::LEFT, _size);
		make(pos, Direction::RIGHT, _size);
		make(pos, Direction::UPLEFT, _size);
		make(pos, Direction::UPRIGHT, _size);
		make(pos, Direction::DOWNLEFT, _size);
		make(pos, Direction::DOWNRIGHT, _size);
	}

	virtual void deleteAll() override {
		powerUpCircles.clear();
	}

	virtual void hideAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end();){
			it->move();
			if(it->outOfBounds()){
				powerUpCircles.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(c, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(*it, f)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(l, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(s, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(t, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(*it, mc)){
				int radius = it->getRadius();
				if(removeOnCollision) powerUpCircles.erase(it);
				return radius;
			}
		}

		return 0;
	}
};

#endif