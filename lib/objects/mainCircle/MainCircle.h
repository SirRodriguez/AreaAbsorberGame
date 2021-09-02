#ifndef MAINCIRCLE_H
#define MAINCIRCLE_H

#include "../../shapes/derivedShapes/Circle.h"
#include "../../Direction.h"
#include "TrapSquare.h"
#include "Car.h"
#include "BuddyCircle.h"

class MainCircle: public Circle{
protected:
	TrapSquare trapSquare;
	Car car;
	BuddyCircle buddy;

	Direction dir;

	int lives;
	int initialRadius;
	int baseSpeed;

	int getTrappedSpeed(){ return speed / 2; }

	// Move at certain speed
	void moveUp(int pixels){ movePosition(olc::vi2d(0, -pixels)); }
	void moveDown(int pixels){ movePosition(olc::vi2d(0, pixels)); }
	void moveLeft(int pixels){ movePosition(olc::vi2d(-pixels, 0)); }
	void moveRight(int pixels){ movePosition(olc::vi2d(pixels, 0)); }
	void moveUpLeft(int pixels){ movePosition(olc::vi2d(-pixels, -pixels)); }
	void moveUpRight(int pixels){ movePosition(olc::vi2d(pixels, -pixels)); }
	void moveDownLeft(int pixels){ movePosition(olc::vi2d(-pixels, pixels)); }
	void moveDownRight(int pixels){ movePosition(olc::vi2d(pixels, pixels)); }

	// Move at default speed unless car is active
	void moveUp() override { moveUp(inCar() ? speed * 2 : speed); }
	void moveDown() override { moveDown(inCar() ? speed * 2 : speed); }
	void moveLeft() override { moveLeft(inCar() ? speed * 2 : speed); }
	void moveRight() override { moveRight(inCar() ? speed * 2 : speed); }
	void moveUpLeft() override { moveUpLeft(inCar() ? speed * 2 : speed); }
	void moveUpRight() override { moveUpRight(inCar() ? speed * 2 : speed); }
	void moveDownLeft() override { moveDownLeft(inCar() ? speed * 2 : speed); }
	void moveDownRight() override { moveDownRight(inCar() ? speed * 2 : speed); }

public:
	MainCircle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d pos, int _speed, const olc::Pixel& _color, int _initialRadius, int newLives, const olc::Pixel& carColor, const olc::Pixel& wheelColor, int carRadius, int buddySpeed, const olc::Pixel& buddyColor)
	: Circle(pge, ac, pos, _speed, _color, _initialRadius), 
		lives(newLives),
		initialRadius(_initialRadius),
		baseSpeed(_speed),
		trapSquare(TrapSquare(pge, ac, pos, _speed, _color, _initialRadius)), 
		car(Car(pge, ac, pos, _speed, carColor, wheelColor, carRadius)),
		buddy(BuddyCircle(pge, ac, pos, buddySpeed, buddyColor, 0, 0)),
		dir(Direction::DOWN){}

	virtual ~MainCircle(){}

	// Lives
	bool alive(){ return lives > 0; }

	// Drawing
	void draw() override {
		car.draw();

		buddy.draw();

		// Draw the main circle
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		olc::vf2d offset = { (whiteCirclePixelWidth * whiteCircleScaleToOneRadius * radius) / 2, (whiteCirclePixelHeight * whiteCircleScaleToOneRadius * radius) / 2 };
		pixelGameEngine->DrawDecal(positionVector - offset, circleDecal, { whiteCircleScaleToOneRadius * radius, whiteCircleScaleToOneRadius * radius }, color);

		trapSquare.draw();
	}

	// Movement
	void move() override {
		if(trapSquare.isNotActive()){
			// Check if the shift is held for speed boost
			if(shiftButton.bHeld && getRadius() > 1){
				speed = baseSpeed * 2;
				grow(-1);
			}else{
				speed = baseSpeed;
			}

			// Move the main circle
			if(upButton.bHeld && belowTopOfScreen()){
				moveUp();
			}
			if(downButton.bHeld && aboveBottomOfScreen()){
				moveDown();
			}
			if(leftButton.bHeld && rightOfLeftOfScreen()){
				moveLeft();
			}
			if(rightButton.bHeld && leftOfRightOfScreen()){
				moveRight();
			}

		}

		// Move the trap to the main circle
		trapSquare.setPosition(getPosition());

		// This is to change its life
		trapSquare.move();

		// Move the car to the main circle
		car.setPosition(getPosition());

		// To move its pedals
		car.move();

		// Move the buddy circle
		buddy.move(*this);
	}

	// Size
	void grow(int amount){ addRadius(amount); }

	// 
	// Trap Square functions
	// 
	void activateTrap(){
		if(inCar()){
			trapSquare.setLength(40 + 20);
		}else{
			trapSquare.setLength(getRadius() * 2 + getRadius() / 2);
		}
		trapSquare.activate();	
	}
	void inactivateTrap(){ trapSquare.inactivate(); }
	bool isTrapped(){ return trapSquare.isActive(); }
	bool isNotTrapped(){ return !isTrapped(); }

	TrapSquare& getTrapSquare(){ return trapSquare; }

	// 
	// Circle Car functions
	// 
	void activateCar(){	car.activate(); }
	void inactivateCar(){ car.inactivate(); }
	bool inCar(){ return car.isActive(); }
	bool notInCar(){ return !inCar(); }

	Car& getCar(){ return car; }
	void hitCar(int value){ car.loseLife(value); }

	int getCarLife(){ return car.getLife(); }

	// 
	// Buddy Circle functions
	// 
	int getBuddyRadius(){ return buddy.getRadius(); }
	bool buddyAlive(){ return buddy.alive(); }
	bool buddyNotAlive(){ return !buddyAlive(); }
	void killBuddy(){ buddy.kill(); }
	BuddyCircle& getBuddy(){ return buddy; }
	void growBuddy(int amount){ if(buddyAlive()) buddy.grow(amount); }
	void addLifeToBuddy(int amount){ buddy.addLife(amount); }
	void reduceLifeToBuddy(int amount){ buddy.subtractLife(amount); }



	void inactivateObjects(){
		inactivateTrap();
		inactivateCar();
		killBuddy();
	}
};

#endif