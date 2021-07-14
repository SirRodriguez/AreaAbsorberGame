#ifndef NEEDLELIST_H
#define NEEDLELIST_H

#include "../../objects/Needle.h"
#include "../ShapeList.h"

#define ENEMYCODE 0

class NeedleList: public ShapeList{
protected:
	std::list<Needle> needles;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel needleColor = olc::BLACK;
		const uint8_t needleSpeed = 6;
		const uint8_t maxNeedleLength = 50;

		needles.push_back(Needle(*pixelGameEngine, _loc, needleSpeed, needleColor, rand() % maxNeedleLength, rand() % maxNeedleLength, dirCode));
	}

public:
	NeedleList()
	: ShapeList(ENEMYCODE){}
	NeedleList(olc::PixelGameEngine& pge)
	: ShapeList(pge, ENEMYCODE){}

	virtual void deleteAll() override {
		needles.clear();
	}

	virtual void hideAll() override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = needles.begin(); it != needles.end();){
			it->move();
			if(it->outOfBounds()){
				needles.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(circleLineCollision(c, *it)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}
		
		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(lineFlowerCollision(*it, f)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(lineLineCollision(*it, l)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(lineSquareCollision(*it, s)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(lineTriangleCollision(*it, t)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}
};

#endif