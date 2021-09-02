#ifndef POWERCIRCLELIST_H
#define POWERCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/powerUp/PowerUpCircle.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class PowerUpCircleList: public ShapeList{
protected:
	std::list<PowerUpCircle*> powerUpCircles;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_size;

	virtual void make(olc::vi2d _loc, Direction dirCode, uint8_t _size){
		powerUpCircles.push_back(new PowerUpCircle(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, _size, dirCode));
	}

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		powerUpCircles.push_back(new PowerUpCircle(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, default_size, dirCode));
	}

public:
	PowerUpCircleList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed, uint8_t _size)
	: ShapeList(pge, ac, ShapeType::BUDDY), default_color(_color), default_speed(_speed), default_size(_size){}

	~PowerUpCircleList(){
		deleteAll();
	}

	virtual void add(olc::vi2d pos) {
		make(pos, Direction::UP);
		make(pos, Direction::DOWN);
		make(pos, Direction::LEFT);
		make(pos, Direction::RIGHT);
		make(pos, Direction::UPLEFT);
		make(pos, Direction::UPRIGHT);
		make(pos, Direction::DOWNLEFT);
		make(pos, Direction::DOWNRIGHT);
	}

	virtual void add(olc::vi2d pos, uint8_t _size){
		make(pos, Direction::UP, _size);
		make(pos, Direction::DOWN, _size);
		make(pos, Direction::LEFT, _size);
		make(pos, Direction::RIGHT, _size);
		make(pos, Direction::UPLEFT, _size);
		make(pos, Direction::UPRIGHT, _size);
		make(pos, Direction::DOWNLEFT, _size);
		make(pos, Direction::DOWNRIGHT, _size);
	}

	virtual void deleteAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			delete *it;
		powerUpCircles.clear();
	}

	virtual void drawAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			(*it)->draw();
	}

	virtual void moveAll() override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end();){
			(*it)->move();
			if((*it)->outOfBounds()){
				delete *it;
				powerUpCircles.erase(it++);
			}else{
				++it;
			}
		}
	}

	// 
	// Movemets to shape
	// 

	virtual void attract(ShapeList& list) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			list.attract(*(*it));
	}

	virtual void attract(Circle& c) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(c, *(*it))){
				(*it)->moveToPos(c.getPosition(), getSuckSpeed((*it)->getPosition(), c.getPosition()));
				c.moveToPos((*it)->getPosition(), getSuckSpeed(c.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Flower& f) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(f, *(*it))){
				(*it)->moveToPos(f.getPosition(), getSuckSpeed((*it)->getPosition(), f.getPosition()));
				f.moveToPos((*it)->getPosition(), getSuckSpeed(f.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Line& l) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(l, *(*it))){
				(*it)->moveToPos(l.getPosition(), getSuckSpeed((*it)->getPosition(), l.getPosition()));
				l.moveToPos((*it)->getPosition(), getSuckSpeed(l.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Square& s) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(s, *(*it))){
				(*it)->moveToPos(s.getPosition(), getSuckSpeed((*it)->getPosition(), s.getPosition()));
				s.moveToPos((*it)->getPosition(), getSuckSpeed(s.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Triangle& t) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(t, *(*it))){
				(*it)->moveToPos(t.getPosition(), getSuckSpeed((*it)->getPosition(), t.getPosition()));
				t.moveToPos((*it)->getPosition(), getSuckSpeed(t.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(MainCircle& mc) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it)
			if(!collision(mc, *(*it))){
				(*it)->moveToPos(mc.getPosition(), getSuckSpeed((*it)->getPosition(), mc.getPosition()));
				mc.moveToPos((*it)->getPosition(), getSuckSpeed(mc.getPosition(), (*it)->getPosition()));
			}
	}

	// 
	// Collision Detections
	// 

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(list.checkCollisionsWith(*(*it)) > 0){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(c, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(*(*it), f)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(l, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(s, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(t, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = powerUpCircles.begin(); it != powerUpCircles.end(); ++it){
			if(collision(*(*it), mc)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					powerUpCircles.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}
};

#endif