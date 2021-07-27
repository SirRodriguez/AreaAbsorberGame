#ifndef BUDDYPOWERUPLIST_H
#define BUDDYPOWERUPLIST_H

#include "../ShapeList.h"
#include "../../objects/BuddyPowerUp.h"

#define POWERUPCODE 2

class BuddyPowerUpList: public ShapeList{
protected:
	std::list<BuddyPowerUp> buddyPowerUps;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_length;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		buddyPowerUps.push_back(BuddyPowerUp(*pixelGameEngine, _loc, default_speed, default_color, default_length, dirCode));
	}

public:
	BuddyPowerUpList()
	: ShapeList(POWERUPCODE){}
	BuddyPowerUpList(olc::PixelGameEngine& pge, olc::Pixel _color, uint8_t _speed, uint8_t _length)
	: ShapeList(pge, POWERUPCODE), default_color(_color), default_speed(_speed), default_length(_length){}

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

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = buddyPowerUps.begin(); it != buddyPowerUps.end(); ++it){
			if(collision(*it, mc)){
				int length = it->getLength();
				if(removeOnCollision) buddyPowerUps.erase(it);
				return length;
			}
		}

		return 0;
	}
};

#endif