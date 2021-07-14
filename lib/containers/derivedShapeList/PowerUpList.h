#ifndef POWERUPLIST_H
#define POWERUPLIST_H

#include "../ShapeList.h"
#include "../../objects/powerUp/PowerUp.h"

#define POWERUPCODE 2

class PowerUpList: public ShapeList{
protected:
	std::list<PowerUp> powerUps;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel powerUpColor = olc::GREEN;
		const uint8_t powerUpSpeed = 2;
		const uint8_t powerUpHeight = 50;

		powerUps.push_back(PowerUp(*pixelGameEngine, _loc, powerUpSpeed, powerUpColor, powerUpHeight, dirCode));

	}

public:
	PowerUpList()
	: ShapeList(ENEMYCODE){}
	PowerUpList(olc::PixelGameEngine& pge)
	: ShapeList(pge, ENEMYCODE){}

	virtual void deleteAll() override {
		powerUps.clear();
	}

	virtual void hideAll() override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = powerUps.begin(); it != powerUps.end();){
			it->move();
			if(it->outOfBounds()){
				powerUps.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(circleTriangleCollision(c, *it)){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(triangleFlowerCollision(*it, f)){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(lineTriangleCollision(l, *it)){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(squareTriangleCollision(s, *it)){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = powerUps.begin(); it != powerUps.end(); ++it){
			if(triangleTriangleCollision(t, *it)){
				int height = it->getHeight();
				if(removeOnCollision) powerUps.erase(it);
				return height;
			}
		}

		return 0;
	}
};

#endif