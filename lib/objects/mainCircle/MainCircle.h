#ifndef MAINCIRCLE_H
#define MAINCIRCLE_H

#include "../../shapes/derivedShapes/Circle.h"
#include "TrapSquare.h"
#include "Car.h"
#include "BuddyCircle.h"

class MainCircle: public Circle{
private:
	enum Direction{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UPLEFT,
		UPRIGHT,
		DOWNLEFT,
		DOWNRIGHT
	};

protected:
	TrapSquare trapSquare;
	Car car;
	BuddyCircle buddy;

	Direction dir;

	int lives;

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

	// Drawing
	void drawWithColor(const olc::Pixel& colorToDraw) override {
		// if(alive() || colorToDraw == olc::WHITE){
		// 	// Draw the circle
		// 	pixelGameEngine->FillCircle(position, radius, colorToDraw);

		// 	// Draw the amount of life
		// 	int textScale = 2;
		// 	std::string lives_string = std::to_string(lives);
		// 	olc::vi2d livesStringSize = pixelGameEngine->GetTextSize(lives_string);
		// 	pixelGameEngine->DrawString(position.x - textScale * (livesStringSize.x / 2), position.y, lives_string, colorToDraw == olc::WHITE ? olc::WHITE : olc::GREY, textScale);
		// }


		car.draw();

		buddy.draw();

		pixelGameEngine->FillCircle(position, radius, colorToDraw);

		trapSquare.draw();
	}

public:
	MainCircle()
	: Circle(), lives(0), trapSquare(TrapSquare()), car(Car()), buddy(BuddyCircle()){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives, const olc::Pixel& carColor, const olc::Pixel& wheelColor, int carRadius, int buddySpeed, const olc::Pixel& buddyColor)
	: Circle(pge, pos, _speed, _color, newRadius), 
		lives(newLives), 	
		trapSquare(TrapSquare(pge, pos, _speed, _color, newRadius)), 
		car(Car(pge, pos, _speed, carColor, wheelColor, carRadius)),
		buddy(BuddyCircle(pge, pos, buddySpeed, buddyColor, 0, 0)),
		dir(Direction::DOWN){}

	// Lives
	bool alive(){ return lives > 0; }

	// Movement
	void move() override {
		if(trapSquare.isNotActive()){
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

		}else if(aboveBottomOfScreen()){
			// Move the main circle
			// moveDown(getTrappedSpeed());
			// Direction the trap was going
			switch(dir){
				case 0: moveUp(getTrappedSpeed()); break;
				case 1: moveDown(getTrappedSpeed()); break;
				case 2: moveLeft(getTrappedSpeed()); break;
				case 3: moveRight(getTrappedSpeed()); break;
				case 4: moveUpLeft(getTrappedSpeed()); break;
				case 5: moveUpRight(getTrappedSpeed()); break;
				case 6: moveDownLeft(getTrappedSpeed()); break;
				case 7: moveDownRight(getTrappedSpeed()); break;
				default: break;
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
	void activateTrap(int directionCode){
		// Direction the trap was going
		switch(directionCode){
			case 0: dir = Direction::UP; break;
			case 1: dir = Direction::DOWN; break;
			case 2: dir = Direction::LEFT; break;
			case 3: dir = Direction::RIGHT; break;
			case 4: dir = Direction::UPLEFT; break;
			case 5: dir = Direction::UPRIGHT; break;
			case 6: dir = Direction::DOWNLEFT; break;
			case 7: dir = Direction::DOWNRIGHT; break;
			default: dir = Direction::DOWN; break;
		}

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

	// Drawing
	void clear() override {
		// Clear the main circle
		drawWithColor(olc::WHITE);

		// Clear the trap
		trapSquare.clear();

		// Clear the car
		car.clear();

		// Clear the buddy circle
		buddy.clear();
	}

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