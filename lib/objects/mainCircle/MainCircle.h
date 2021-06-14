#ifndef MAINCIRCLE_H
#define MAINCIRCLE_H

#include "..\..\shapes\derivedShapes\Circle.h"
#include "TrapSquare.h"

class MainCircle: public Circle{
protected:
	TrapSquare trapSquare;

	int lives;

	int getTrappedSpeed(){
		speed / 2;
	}

	void moveUp(int pixels){ movePosition(olc::vi2d(0, -pixels)); }
	void moveDown(int pixels){ movePosition(olc::vi2d(0, pixels)); }
	void moveLeft(int pixels){ movePosition(olc::vi2d(-pixels, 0)); }
	void moveRight(int pixels){ movePosition(olc::vi2d(pixels, 0)); }

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


		pixelGameEngine->FillCircle(position, radius, colorToDraw);

		trapSquare.draw();
	}

public:
	MainCircle()
	: Circle(), lives(0), trapSquare(TrapSquare()){}
	MainCircle(olc::PixelGameEngine& pge)
	: Circle(pge), lives(0), trapSquare(TrapSquare(pge)){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos), lives(0), trapSquare(TrapSquare(pge, pos)){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Circle(pge, pos, _speed), lives(0), trapSquare(TrapSquare(pge, pos, _speed)){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Circle(pge, pos, _speed, _color), lives(0), trapSquare(TrapSquare(pge, pos, _speed, _color)){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Circle(pge, pos, _speed, _color, newRadius), lives(0), trapSquare(TrapSquare(pge, pos, _speed, _color, newRadius)){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives)
	: Circle(pge, pos, _speed, _color, newRadius), lives(newLives), trapSquare(TrapSquare(pge, pos, _speed, _color, newRadius)){}

	// Lives
	bool alive(){ return lives > 0; }

	// Movement
	void move() override {
		if(trapSquare.isNotActive()){
			// Move the main circle
			if(upButton.bHeld && belowTopOfScreen()){
				moveUp(speed);
			}
			if(downButton.bHeld && aboveBottomOfScreen()){
				moveDown(speed);
			}
			if(leftButton.bHeld && rightOfLeftOfScreen()){
				moveLeft(speed);
			}
			if(rightButton.bHeld && leftOfRightOfScreen()){
				moveRight(speed);
			}

			// Move the trap to the main circle
			trapSquare.setPosition(getPosition());

		}else if(aboveBottomOfScreen()){
			// Move the main circle
			moveDown(getTrappedSpeed());

			// Move the trap to the main circle
			trapSquare.setPosition(getPosition());
		}

		// This is to change its life
		trapSquare.move();
	}

	// Size
	void grow(int amount){ addRadius(amount); }

	// Trap Square functions
	void activateTrap(){
		trapSquare.setLength(getRadius() * 2 + getRadius() / 2);
		trapSquare.activate();	
	}

	// Drawing
	void clear() override {
		// Clear the main circle
		drawWithColor(olc::WHITE);

		// Clear the trap
		trapSquare.clear();
	}
};

#endif