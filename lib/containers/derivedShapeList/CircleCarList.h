#ifndef CIRCLECARLIST_H
#define CIRCLECARLIST_H

#include "../ShapeList.h"
#include "../../objects/CircleCar.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class CircleCarList: public ShapeList{
protected:
	std::list<CircleCar*> circleCars;
	olc::Pixel default_color;
	olc::Pixel default_wheel_color;
	uint8_t default_speed;
	uint8_t default_radius;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		circleCars.push_back(new CircleCar(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, default_wheel_color, default_radius, dirCode));
	}

public:
	CircleCarList()
	: ShapeList(ShapeType::POWERUP){}
	CircleCarList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, olc::Pixel _wheel_color, uint8_t _speed, uint8_t _radius)
	: ShapeList(pge, ac, ShapeType::POWERUP), default_color(_color), default_wheel_color(_wheel_color), default_speed(_speed), default_radius(_radius){}

	~CircleCarList(){
		deleteAll();
	}

	virtual void deleteAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			delete *it;
		circleCars.clear();
	}

	virtual void hideAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			(*it)->clear();
	}

	virtual void drawAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			(*it)->draw();
	}

	virtual void moveAll() override {
		for(auto it = circleCars.begin(); it != circleCars.end();){
			(*it)->move();
			if((*it)->outOfBounds()){
				delete *it;
				circleCars.erase(it++);
			}else{
				++it;
			}
		}
	}

	// 
	// Movemets to shape
	// 

	virtual void attract(ShapeList& list) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			list.attract(*(*it));
	}

	virtual void attract(Circle& c) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(c, *(*it))){
				(*it)->moveToPos(c.getPosition(), getSuckSpeed((*it)->getPosition(), c.getPosition()));
				c.moveToPos((*it)->getPosition(), getSuckSpeed(c.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Flower& f) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(f, *(*it))){
				(*it)->moveToPos(f.getPosition(), getSuckSpeed((*it)->getPosition(), f.getPosition()));
				f.moveToPos((*it)->getPosition(), getSuckSpeed(f.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Line& l) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(l, *(*it))){
				(*it)->moveToPos(l.getPosition(), getSuckSpeed((*it)->getPosition(), l.getPosition()));
				l.moveToPos((*it)->getPosition(), getSuckSpeed(l.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Square& s) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(s, *(*it))){
				(*it)->moveToPos(s.getPosition(), getSuckSpeed((*it)->getPosition(), s.getPosition()));
				s.moveToPos((*it)->getPosition(), getSuckSpeed(s.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Triangle& t) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(t, *(*it))){
				(*it)->moveToPos(t.getPosition(), getSuckSpeed((*it)->getPosition(), t.getPosition()));
				t.moveToPos((*it)->getPosition(), getSuckSpeed(t.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(MainCircle& mc) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it)
			if(!collision(mc, *(*it))){
				(*it)->moveToPos(mc.getPosition(), getSuckSpeed((*it)->getPosition(), mc.getPosition()));
				mc.moveToPos((*it)->getPosition(), getSuckSpeed(mc.getPosition(), (*it)->getPosition()));
			}
	}

	// 
	// Collision Detections
	// 

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(list.checkCollisionsWith(*(*it)) > 0){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(c, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(*(*it), f)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(l, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(s, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(t, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = circleCars.begin(); it != circleCars.end(); ++it){
			if(collision(*(*it), mc)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					circleCars.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}
};

#endif