#ifndef MAINCIRCLE_H
#define MAINCIRCLE_H

#include "..\shapes\derivedShapes\Circle.h"

class MainCircle: public Circle{
protected:
	int lives;

	void moveUp(int pixels){ movePosition(olc::vi2d(0, -pixels)); }
	void moveDown(int pixels){ movePosition(olc::vi2d(0, pixels)); }
	void moveLeft(int pixels){ movePosition(olc::vi2d(-pixels, 0)); }
	void moveRight(int pixels){ movePosition(olc::vi2d(pixels, 0)); }

	// Drawing
	void draw(const olc::Pixel& colorToDraw) override {
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
	}

public:
	MainCircle()
	: Circle(), lives(0){}
	MainCircle(olc::PixelGameEngine& pge)
	: Circle(pge), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Circle(pge, pos, _speed), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Circle(pge, pos, _speed, _color), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Circle(pge, pos, _speed, _color, newRadius), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives)
	: Circle(pge, pos, _speed, _color, newRadius), lives(newLives){}

	void draw() override {
		draw(color);
	}

	// Lives
	bool alive(){ return lives > 0; }

	// Movement
	void move() override {
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
	}

	// Size
	void grow(int amount){ addRadius(amount); }
};

#endif