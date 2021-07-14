#ifndef BUDDYPOWERUPLIST_H
#define BUDDYPOWERUPLIST_H

#include "../ShapeList.h"
#include "../../objects/BuddyPowerUp.h"

#define POWERUPCODE 2

class BuddyPowerUpList: public ShapeList{
protected:
	std::list<BuddyPowerUp> buddyPowerUps;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel buddyPowerUpColor = olc::YELLOW;
		const uint8_t buddyPowerUpSpeed = 2;
		const uint8_t buddyPowerUpLength = 40;

		buddyPowerUps.push_back(BuddyPowerUp(*pixelGameEngine, _loc, buddyPowerUpSpeed, buddyPowerUpColor, buddyPowerUpLength, dirCode));

	}

public:
	BuddyPowerUpList()
	: ShapeList(POWERUPCODE){}
	BuddyPowerUpList(olc::PixelGameEngine& pge)
	: ShapeList(pge, POWERUPCODE){}

	virtual void deleteAll() override {
		buddyPowerUps.clear();
	}

	virtual void hideAll() override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end();){
			it->move();
			if(it->outOfBounds()){
				buddyPowerUps.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(c, *it)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(*it, f)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(l, *it)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(s, *it)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(t, *it)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}
};

#endif