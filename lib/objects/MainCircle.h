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

public:
	MainCircle()
	: Circle(), lives(0){}
	MainCircle(olc::PixelGameEngine& pge)
	: Circle(pge), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius)
	: Circle(pge, pos, newRadius), lives(0){}
	MainCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius, int newLives)
	: Circle(pge, pos, newRadius), lives(newLives){}

	// Drawing
	void draw(const olc::Pixel& color) override {
		// if(alive() || color == olc::WHITE){
		// 	// Draw the circle
		// 	pixelGameEngine->FillCircle(position, radius, color);

		// 	// Draw the amount of life
		// 	int textScale = 2;
		// 	std::string lives_string = std::to_string(lives);
		// 	olc::vi2d livesStringSize = pixelGameEngine->GetTextSize(lives_string);
		// 	pixelGameEngine->DrawString(position.x - textScale * (livesStringSize.x / 2), position.y, lives_string, color == olc::WHITE ? olc::WHITE : olc::GREY, textScale);
		// }
		pixelGameEngine->FillCircle(position, radius, color);
	}

	// Lives
	bool alive(){ return lives > 0; }

	// Movement
	void move(int pixels) override {
		if(upButton.bHeld && belowTopOfScreen()){
			moveUp(pixels);
		}
		if(downButton.bHeld && aboveBottomOfScreen()){
			moveDown(pixels);
		}
		if(leftButton.bHeld && rightOfLeftOfScreen()){
			moveLeft(pixels);
		}
		if(rightButton.bHeld && leftOfRightOfScreen()){
			moveRight(pixels);
		}
	}

	// Size
	void grow(int amount){ addRadius(amount); }
};

#endif