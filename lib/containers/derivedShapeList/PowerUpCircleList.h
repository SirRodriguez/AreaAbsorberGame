#ifndef POWERCIRCLELIST_H
#define POWERCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/powerUp/PowerUpCircle.h"

#define BUDDYCODE 1

class PowerUpCircleList: public ShapeList{
protected:
	std::list<PowerUpCircle> powerUpCircles;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel powerUpCircleColor = olc::GREY;
		const uint8_t powerUpCircleSpeed = 5;
		const uint8_t powerUpCircleSize = 40;
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, _loc, powerUpCircleSpeed, powerUpCircleColor, powerUpCircleSize, dirCode));
	}

	virtual void make(olc::vi2d _loc, int dirCode, uint8_t _size){
		const olc::Pixel powerUpCircleColor = olc::GREY;
		const uint8_t powerUpCircleSpeed = 5;
		powerUpCircles.push_back(PowerUpCircle(*pixelGameEngine, _loc, powerUpCircleSpeed, powerUpCircleColor, _size, dirCode));
	}

public:
	PowerUpCircleList()
	: ShapeList(BUDDYCODE){}
	PowerUpCircleList(olc::PixelGameEngine& pge)
	: ShapeList(pge, BUDDYCODE){}

	virtual void add(olc::vi2d pos) {
		for(uint8_t dirCode = 0; dirCode <= 7; ++dirCode) make(pos, dirCode);
	}

	virtual void add(olc::vi2d pos, uint8_t _size){
		for(uint8_t dirCode = 0; dirCode <= 7; ++dirCode) make(pos, dirCode, _size);
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