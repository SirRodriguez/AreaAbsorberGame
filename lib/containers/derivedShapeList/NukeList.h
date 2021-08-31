#ifndef NUKELIST_H
#define NUKELIST_H

#include "../ShapeList.h"
#include "../../objects/Nuke.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class NukeList: public ShapeList{
protected:
	std::list<Nuke*> nukes;
	olc::Pixel default_color;
	olc::Pixel default_pedal_color;
	uint8_t default_speed;
	uint8_t default_radius;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		nukes.push_back(new Nuke(*pixelGameEngine, *animationContainer, _loc, default_speed, default_color, default_pedal_color, default_radius, dirCode));
	}

public:
	NukeList()
	: ShapeList(ShapeType::POWERUP){}
	NukeList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, olc::Pixel _pedal_color, uint8_t _speed, uint8_t _radius)
	: ShapeList(pge, ac, ShapeType::POWERUP), default_color(_color), default_pedal_color(_pedal_color), default_speed(_speed), default_radius(_radius){}

	~NukeList(){
		deleteAll();
	}

	virtual void deleteAll() override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			delete *it;
		nukes.clear();
	}

	virtual void hideAll() override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			(*it)->clear();
	}

	virtual void drawAll() override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			(*it)->draw();
	}

	virtual void moveAll() override {
		for(auto it = nukes.begin(); it != nukes.end();){
			(*it)->move();
			if((*it)->outOfBounds()){
				delete *it;
				nukes.erase(it++);
			}else{
				++it;
			}
		}
	}

	// 
	// Movemets to shape
	// 

	virtual void attract(ShapeList& list) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			list.attract(*(*it));
	}

	virtual void attract(Circle& c) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(c, *(*it))){
				(*it)->moveToPos(c.getPosition(), getSuckSpeed((*it)->getPosition(), c.getPosition()));
				c.moveToPos((*it)->getPosition(), getSuckSpeed(c.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Flower& f) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(f, *(*it))){
				(*it)->moveToPos(f.getPosition(), getSuckSpeed((*it)->getPosition(), f.getPosition()));
				f.moveToPos((*it)->getPosition(), getSuckSpeed(f.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Line& l) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(l, *(*it))){
				(*it)->moveToPos(l.getPosition(), getSuckSpeed((*it)->getPosition(), l.getPosition()));
				l.moveToPos((*it)->getPosition(), getSuckSpeed(l.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Square& s) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(s, *(*it))){
				(*it)->moveToPos(s.getPosition(), getSuckSpeed((*it)->getPosition(), s.getPosition()));
				s.moveToPos((*it)->getPosition(), getSuckSpeed(s.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(Triangle& t) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(t, *(*it))){
				(*it)->moveToPos(t.getPosition(), getSuckSpeed((*it)->getPosition(), t.getPosition()));
				t.moveToPos((*it)->getPosition(), getSuckSpeed(t.getPosition(), (*it)->getPosition()));
			}
	}

	virtual void attract(MainCircle& mc) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it)
			if(!collision(mc, *(*it))){
				(*it)->moveToPos(mc.getPosition(), getSuckSpeed((*it)->getPosition(), mc.getPosition()));
				mc.moveToPos((*it)->getPosition(), getSuckSpeed(mc.getPosition(), (*it)->getPosition()));
			}
	}

	// 
	// Collision Detections
	// 

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(list.checkCollisionsWith(*(*it)) > 0){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(c, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(*(*it), f)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(l, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(s, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(t, *(*it))){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		for(auto it = nukes.begin(); it != nukes.end(); ++it){
			if(collision(*(*it), mc)){
				int radius = (*it)->getRadius();
				if(removeOnCollision){
					delete *it;
					nukes.erase(it);
				}
				return radius;
			}
		}

		return 0;
	}

};


#endif