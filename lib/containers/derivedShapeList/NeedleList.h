#ifndef NEEDLELIST_H
#define NEEDLELIST_H

#include "../../objects/needle/Needle.h"
#include "../ShapeList.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class NeedleList: public ShapeList{
protected:
	std::list<Needle*> needles;
	olc::Pixel default_color;
	uint8_t default_speed;
	uint8_t default_max_length;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		needles.push_back(new Needle(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, rand() % default_max_length, rand() % default_max_length, dirCode));
	}

public:
	NeedleList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed, uint8_t _length)
	: ShapeList(pge, ac, ShapeType::ENEMY), default_color(_color), default_speed(_speed), default_max_length(_length){}

	~NeedleList(){
		deleteAll();
	}

	virtual void deleteAll() override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			delete *it;
		needles.clear();
	}

	virtual void drawAll() override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			(*it)->draw();
	}

	virtual void moveAll() override {
		for(auto it = needles.begin(); it != needles.end();){
			(*it)->move();
			if((*it)->outOfBounds()){
				delete *it;
				needles.erase(it++);
			}else{
				++it;
			}
		}
	}

	// 
	// Movemets to shape
	// 

	virtual void attract(ShapeList& list) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			list.attract(*(*it));
	}

	virtual void attract(Circle& c) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(c, *(*it))){
				(*it)->moveToPos(c.getPosition(), getSuckSpeed((*it)->getPosition(), c.getPosition()));
				c.moveToPos((*it)->getPosition(), getSuckSpeed(c.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Flower& f) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(f, *(*it))){
				(*it)->moveToPos(f.getPosition(), getSuckSpeed((*it)->getPosition(), f.getPosition()));
				f.moveToPos((*it)->getPosition(), getSuckSpeed(f.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Line& l) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(l, *(*it))){
				(*it)->moveToPos(l.getPosition(), getSuckSpeed((*it)->getPosition(), l.getPosition()));
				l.moveToPos((*it)->getPosition(), getSuckSpeed(l.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Square& s) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(s, *(*it))){
				(*it)->moveToPos(s.getPosition(), getSuckSpeed((*it)->getPosition(), s.getPosition()));
				s.moveToPos((*it)->getPosition(), getSuckSpeed(s.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Triangle& t) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(t, *(*it))){
				(*it)->moveToPos(t.getPosition(), getSuckSpeed((*it)->getPosition(), t.getPosition()));
				t.moveToPos((*it)->getPosition(), getSuckSpeed(t.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(MainCircle& mc) override {
		for(auto it = needles.begin(); it != needles.end(); ++it)
			if(!collision(mc, *(*it))){
				(*it)->moveToPos(mc.getPosition(), getSuckSpeed((*it)->getPosition(), mc.getPosition()));
				mc.moveToPos((*it)->getPosition(), getSuckSpeed(mc.getPosition(), (*it)->getPosition()));
			}
	}

	// 
	// Collision Detections
	// 

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(list.checkCollisionsWith(*(*it)) > 0){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(c, *(*it))){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}
		
		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*(*it), f)){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*(*it), l)){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*(*it), s)){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*(*it), t)){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = needles.begin(); it != needles.end(); ++it){
			if(collision(*(*it), mc)){
				int length = (*it)->getLength();
				if(removeOnCollision){
					delete *it;
					needles.erase(it);
				}
				return length;
			}
		}

		return 0;
	}
};

#endif