#ifndef NEEDLELIST_H
#define NEEDLELIST_H

#include "../../objects/needle/Needle.h"
#include "../ShapeList.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class NeedleList: public ShapeList{
protected:
	std::list<Needle> needles;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_max_length;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		needles.push_back(Needle(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, rand() % default_max_length, rand() % default_max_length, dirCode));
	}

public:
	NeedleList()
	: ShapeList(ShapeType::ENEMY){}
	NeedleList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed, uint8_t _length)
	: ShapeList(pge, ac, ShapeType::ENEMY), default_color(_color), default_speed(_speed), default_max_length(_length){}

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
			if(collision(c, *it)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}
		
		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*it, f)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*it, l)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*it, s)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*it, t)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*it, mc)){
				int length = it->getLength();
				if(removeOnCollision) needles.erase(it);
				return length;
			}
		}

		return 0;
	}
};

#endif