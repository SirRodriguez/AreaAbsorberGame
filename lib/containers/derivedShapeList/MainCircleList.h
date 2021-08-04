#ifndef MAINCIRCLELIST_H
#define MAINCIRCLELIST_H

// This class will just hold one shape, the main circle

#include "../../objects/mainCircle/MainCircle.h"
#include "../ShapeList.h"
#include "../../Direction.h"
#include "../../ShapeType.h"

class MainCircleList: public ShapeList{
protected:
	MainCircle mainCircle;
	uint8_t default_speed;
	olc::Pixel default_color;
	uint8_t default_initial_size;
	olc::Pixel default_circle_car_color;
	olc::Pixel default_circle_car_wheel_color;
	uint8_t default_circle_car_radius;
	uint8_t default_buddy_circle_speed;
	olc::Pixel default_buddy_circle_color;

	virtual void make(olc::vi2d _loc, Direction dirCode) override {}

public:
	MainCircleList()
	: ShapeList(ShapeType::MAINCIRCLE){}
	MainCircleList(
		olc::PixelGameEngine& pge, 
		uint32_t _speed, 
		olc::Pixel _color, 
		uint8_t _initial_size, 
		olc::Pixel _circle_car_color, 
		olc::Pixel _cirlce_car_wheel_color, 
		uint8_t _circle_car_radius, 
		uint8_t _buddy_circle_speed, 
		olc::Pixel _buddy_circle_color
	)
	: ShapeList(pge, ShapeType::MAINCIRCLE), 
		default_speed(_speed),
		default_color(_color),
		default_initial_size(_initial_size),
		default_circle_car_color(_circle_car_color),
		default_circle_car_wheel_color(_cirlce_car_wheel_color),
		default_circle_car_radius(_circle_car_radius),
		default_buddy_circle_speed(_buddy_circle_speed),
		default_buddy_circle_color(_buddy_circle_color)
		{
		olc::vi2d centerPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		uint8_t numLives = 0;
		mainCircle = MainCircle(
			pge,
			centerPos,
			default_speed,
			default_color, 
			default_initial_size, 
			numLives,
			default_circle_car_color,
			default_circle_car_wheel_color,
			default_circle_car_radius,
			default_buddy_circle_speed,
			default_buddy_circle_color
		);
	}

	virtual void deleteAll() override {}

	virtual void hideAll() override {
		mainCircle.clear();
	}

	virtual void drawAll() override {
		mainCircle.draw();
	}

	virtual void moveAll() override {
		mainCircle.move();
	}

	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) override {
		return list.checkCollisionsWith(mainCircle) > 0 ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) override {
		return collision(mainCircle, c) ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) override {
		return collision(mainCircle, f) ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) override {
		return collision(mainCircle, l) ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) override {
		return collision(mainCircle, s) ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) override {
		return collision(mainCircle, t) ? mainCircle.getRadius() : 0;
	}

	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) override {
		return 0;
	}

	void resetObjects(){
		mainCircle.inactivateObjects();
	}

	// Trap Square functions
	void activateTrap(){
		mainCircle.activateTrap();
	}
	void inactivateTrap(){
		mainCircle.inactivateTrap();
	}
	bool isTrapped(){
		return mainCircle.isTrapped();
	}
	bool isNotTrapped(){
		return mainCircle.isNotTrapped();
	}
	TrapSquare& getTrapSquare(){
		return mainCircle.getTrapSquare();
	}

	// Circle Car functions
	void activateCar(){	mainCircle.activateCar(); }
	void inactivateCar(){ mainCircle.inactivateCar(); }
	bool inCar(){ return mainCircle.inCar(); }
	bool notInCar(){ return mainCircle.notInCar(); }

	Car& getCar(){ return mainCircle.getCar(); }
	void hitCar(int value){ mainCircle.hitCar(value); }

	int getCarLife(){ return mainCircle.getCarLife(); }

	// Buddy Circle Functions
	int getBuddyRadius(){ return mainCircle.getBuddyRadius(); }
	bool buddyAlive(){ return mainCircle.buddyAlive(); }
	bool buddyNotAlive(){ return mainCircle.buddyNotAlive(); }
	void killBuddy(){ mainCircle.killBuddy(); }
	BuddyCircle& getBuddy(){ return mainCircle.getBuddy(); }
	void growBuddy(int amount){ mainCircle.growBuddy(amount); }
	void addLifeToBuddy(int amount){ mainCircle.addLifeToBuddy(amount); }
	void reduceLifeToBuddy(int amount){ mainCircle.reduceLifeToBuddy(amount); }

	// Size
	void setRadius(int value){
		mainCircle.setRadius(value);
	}
	int getRadius(){
		return mainCircle.getRadius();
	}
	void grow(int amount){
		mainCircle.addRadius(amount);
		mainCircle.growBuddy(amount);
	}

	// Position
	olc::vi2d getPosition(){
		return mainCircle.getPosition();
	}
	void setPosition(olc::vi2d pos){
		mainCircle.setPosition(pos);
	}

};

#endif