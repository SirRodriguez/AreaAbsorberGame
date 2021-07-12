#ifndef OTHERCIRCLELIST_H
#define OTHERCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/OtherCircle.h"

#define ENEMYCODE 0

class OtherCircleList: public ShapeList{
protected:
	std::list<OtherCircle> otherCircle;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel otherCircleColor = olc::RED;
		const uint8_t otherCircleSpeed = 4;
		const uint8_t otherCircleMaxRadius = 50;
		otherCircle.push_back(OtherCircle(*pixelGameEngine, _loc, otherCircleSpeed, otherCircleColor, rand() % otherCircleMaxRadius, dirCode));
	}

public:
	OtherCircleList()
	: ShapeList(ENEMYCODE){}
	OtherCircleList(olc::PixelGameEngine& pge)
	: ShapeList(pge, ENEMYCODE){}

	virtual void deleteAll() override {
		otherCircle.clear();
	}

	virtual void hideAll() override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = otherCircle.begin(); it != otherCircle.end();){
			it->move();
			if(it->outOfBounds()){
				otherCircle.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			int collideNum = list.checkCollisionsWith(*it, removeOnCollision);
			if(collideNum > 0){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(circleCircleCollision(c, *it)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(circleFlowerCollision(*it, f)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(circleLineCollision(*it, l)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(circleSquareCollision(*it, s)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}
};

#endif