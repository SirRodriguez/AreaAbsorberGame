#ifndef BOSSCIRCLELIST_H
#define BOSSCIRCLELIST_H

#include "../ShapeList.h"
#include "../../objects/BossCircle.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class BossCircleList: public ShapeList{
protected:
	BossCircle* boss;
	bool alive;
	olc::Pixel default_color;
	uint8_t default_speed;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {
		if(!alive){
			alive = true;

			// Adjust direction
			boss->changeDirection(dirCode);

			// Adjust radius
			int radius;
			switch(dirCode){
				case Direction::UP:
				case Direction::DOWN: radius = pixelGameEngine->ScreenWidth() / 2; break;
				case Direction::LEFT:
				case Direction::RIGHT: radius = pixelGameEngine->ScreenHeight() / 2; break;
				case Direction::UPRIGHT:
				case Direction::UPLEFT:
				case Direction::DOWNLEFT:
				case Direction::DOWNRIGHT:
				default: radius = std::max(pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()) / 2; break;
			}
			boss->setRadius(radius);

			// Adjust Location
			switch(dirCode){
				case Direction::UP: _loc += olc::vi2d(0, radius); break;
				case Direction::DOWN: _loc += olc::vi2d(0, -radius); break;
				case Direction::LEFT: _loc += olc::vi2d(radius, 0); break;
				case Direction::RIGHT: _loc += olc::vi2d(-radius, 0); break;
				case Direction::UPRIGHT: _loc += olc::vi2d(-radius, radius); break;
				case Direction::UPLEFT: _loc += olc::vi2d(radius, radius); break;
				case Direction::DOWNLEFT: _loc += olc::vi2d(radius, -radius); break;
				case Direction::DOWNRIGHT: _loc += olc::vi2d(-radius, -radius); break;
				default: break;
			}
			boss->setPosition(_loc);
		}
	}

public:
	BossCircleList(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::Pixel _color, uint8_t _speed)
	: ShapeList(pge, ac, ShapeType::ENEMY), 
		default_color(_color), 
		default_speed(_speed), 
		alive(false), 
		boss(new BossCircle(pge, ac, olc::vi2d(0,0), _speed, _color, 0, Direction::DOWN)){}

	~BossCircleList(){
		deleteAll();
		delete boss;
	}

	virtual void deleteAll() override {
		alive = false;
	}

	virtual void drawAll() override {
		if(alive) boss->draw();
	}

	virtual void moveAll() override {
		if(!alive) return;

		boss->move();
		if(boss->outOfBounds()) deleteAll();
	}

	// 
	// Movemets to shape
	// 

	virtual void attract(ShapeList& list) override {
		if(alive) list.attract(*boss);
	}

	virtual void attract(Circle& c) override {
		if(!collision(c, *boss)){
			boss->moveToPos(c.getPosition(), getSuckSpeed(boss->getPosition(), c.getPosition()));
			c.moveToPos(boss->getPosition(), getSuckSpeed(c.getPosition(), boss->getPosition()));
		}
	}

	virtual void attract(Flower& f) override {
		if(!collision(f, *boss)){
			boss->moveToPos(f.getPosition(), getSuckSpeed(boss->getPosition(), f.getPosition()));
			f.moveToPos(boss->getPosition(), getSuckSpeed(f.getPosition(), boss->getPosition()));
		}
	}

	virtual void attract(Line& l) override {
		if(!collision(l, *boss)){
			boss->moveToPos(l.getPosition(), getSuckSpeed(boss->getPosition(), l.getPosition()));
			l.moveToPos(boss->getPosition(), getSuckSpeed(l.getPosition(), boss->getPosition()));
		}
	}

	virtual void attract(Square& s) override {
		if(!collision(s, *boss)){
			boss->moveToPos(s.getPosition(), getSuckSpeed(boss->getPosition(), s.getPosition()));
			s.moveToPos(boss->getPosition(), getSuckSpeed(s.getPosition(), boss->getPosition()));
		}
	}

	virtual void attract(Triangle& t) override {
		if(!collision(t, *boss)){
			boss->moveToPos(t.getPosition(), getSuckSpeed(boss->getPosition(), t.getPosition()));
			t.moveToPos(boss->getPosition(), getSuckSpeed(t.getPosition(), boss->getPosition()));
		}
	}

	virtual void attract(MainCircle& mc) override {
		if(!collision(mc, *boss)){
			boss->moveToPos(mc.getPosition(), getSuckSpeed(boss->getPosition(), mc.getPosition()));
			mc.moveToPos(boss->getPosition(), getSuckSpeed(mc.getPosition(), boss->getPosition()));
		}
	}

	// 
	// Collision Detections
	// 

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		if(alive && list.checkCollisionsWith(*boss) > 0){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;

	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		if(alive && collision(c, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		if(alive && collision(f, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		if(alive && collision(l, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		if(alive && collision(s, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}

	virtual checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		if(alive && collision(t, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		if(alive && collision(mc, *boss)){
			int radius = boss->getRadius();
			if(removeOnCollision) deleteAll();
			return radius;
		}

		return 0;
	}
};

#endif