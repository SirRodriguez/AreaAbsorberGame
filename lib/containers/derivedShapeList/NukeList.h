#ifndef NUKELIST_H
#define NUKELIST_H

#include "../ShapeList.h"
#include "../../objects/Nuke.h"

#define POWERUPCODE 2

class NukeList: public ShapeList{
protected:
	std::list<Nuke> nukes;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel nukeColor = olc::BLACK;
		const olc::Pixel nukePedalColor = olc::DARK_RED;
		const uint8_t nukeSpeed = 6;
		const uint8_t nukeRadius = 30;

		nukes.push_back(Nuke(*pixelGameEngine, _loc, nukeSpeed, nukeColor, nukePedalColor, nukeRadius, dirCode));

	}

public:
	NukeList()
	: ShapeList(ENEMYCODE){}
	NukeList(olc::PixelGameEngine& pge)
	: ShapeList(pge, ENEMYCODE){}

	virtual void deleteAll() override {
		nukes.clear();
	}

	virtual void hideAll() override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = nukes.begin(); it != nukes.end();){
			it->move();
			if(it->outOfBounds()){
				nukes.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(list.checkCollisionsWith(*it, removeOnCollision) > 0){
				int radius = it->getRadius();
				if(removeOnCollision) nukes.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(circleFlowerCollision(c, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) nukes.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(flowerFlowerCollision(*it, f)){
				int radius = it->getRadius();
				if(removeOnCollision) nukes.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(lineFlowerCollision(l, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) nukes.erase(it);
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(squareFlowerCollision(s, *it)){
				int radius = it->getRadius();
				if(removeOnCollision) nukes.erase(it);
				return radius;
			}
		}

		return 0;
	}

};


#endif