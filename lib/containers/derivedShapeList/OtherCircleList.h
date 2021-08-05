#ifndef OTHERCIRCLELIST_H
#define OTHERCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/OtherCircle.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class OtherCircleList: public ShapeList{
protected:
	std::list<OtherCircle> otherCircle;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_max_radius;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		otherCircle.push_back(OtherCircle(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, rand() % default_max_radius, dirCode));
	}

public:
	OtherCircleList()
	: ShapeList(ShapeType::ENEMY){}
	OtherCircleList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed, uint8_t _radius)
	: ShapeList(pge, ac, ShapeType::ENEMY), default_color(_color), default_speed(_speed), default_max_radius(_radius){}

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
			if(list.checkCollisionsWith(*it) > 0){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(c, *it)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(*it, f)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(*it, l)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(*it, s)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(*it, t)){
				int otherRadius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return otherRadius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
			if(collision(*it, mc)){
				int radius = it->getRadius();
				if(removeOnCollision) otherCircle.erase(it);
				return radius;
			}
		}

		return 0;
	}
};

#endif