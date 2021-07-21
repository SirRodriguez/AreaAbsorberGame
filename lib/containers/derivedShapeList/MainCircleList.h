#ifndef MAINCIRCLELIST_H
#define MAINCIRCLELIST_H

// This class will just hold one shape, the main circle

#include "../../objects/mainCircle/MainCircle.h"
#include "../ShapeList.h"

#define MAINCIRCLECODE 3

class MainCircleList: public ShapeList{
protected:
	MainCircle mainCircle;

	virtual void make(olc::vi2d _loc, int dirCode) override {}

public:
	MainCircleList()
	: ShapeList(MAINCIRCLECODE){}
	MainCircleList(olc::PixelGameEngine& pge)
	: ShapeList(pge, MAINCIRCLECODE){
		const uint8_t mainCircleSpeed = 5;
		const olc::Pixel mainCircleColor = olc::BLACK;
		const uint8_t initialMainCircleSize = 10;
		const olc::Pixel circleCarColor = olc::BLUE;
		const olc::Pixel circleCarWheelColor = olc::BLACK;
		const uint8_t circleCarRadius = 40;
		const uint8_t buddyCircleSpeed = 2;
		const olc::Pixel buddyCircleColor = olc::DARK_GREY;

		olc::vi2d centerPos = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		uint8_t numLives = 0;
		mainCircle = MainCircle(
			pge,
			centerPos,
			mainCircleSpeed,
			mainCircleColor, 
			initialMainCircleSize, 
			numLives,
			circleCarColor,
			circleCarWheelColor,
			circleCarRadius,
			buddyCircleSpeed,
			buddyCircleColor
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
	void activateTrap(int dirCode){
		mainCircle.activateTrap(dirCode);
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