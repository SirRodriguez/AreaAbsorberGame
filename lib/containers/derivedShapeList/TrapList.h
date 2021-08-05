#ifndef TRAPLIST_H
#define TRAPLIST_H

#include "../ShapeList.h"
#include "../../objects/Trap.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class TrapList: public ShapeList{
protected:
	std::list<Trap> traps;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_length;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		traps.push_back(Trap(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, default_length, dirCode));
	}

public:
	TrapList()
	: ShapeList(ShapeType::ENEMY){}
	TrapList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed, uint8_t _length)
	: ShapeList(pge, ac, ShapeType::ENEMY), default_color(_color), default_speed(_speed), default_length(_length){}

	virtual void deleteAll() override {
		traps.clear();
	}

	virtual void hideAll() override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = traps.begin(); it != traps.end();){
			it->move();
			if(it->outOfBounds()){
				traps.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(list.checkCollisionsWith(*it) > 0){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(c, *it)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(*it, f)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(l, *it)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(*it, s)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(*it, t)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(collision(*it, mc)){
				int dirCode = it->getLength();
				if(removeOnCollision) traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

};

#endif