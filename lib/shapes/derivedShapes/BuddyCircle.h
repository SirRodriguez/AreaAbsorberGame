#ifndef BUDDYCIRCLE_H
#define BUDDYCIRCLE_H

#include "..\..\utils.h"
#include ".\Circle.h"

class BuddyCircle: public Circle{
protected:
	int lives;

public:
	BuddyCircle()
	: Circle(), lives(0){}
	BuddyCircle(olc::PixelGameEngine& pge)
	: Circle(pge), lives(0){}
	BuddyCircle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Circle(pge, pos), lives(0){}
	BuddyCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius)
	: Circle(pge, pos, newRadius), lives(0){}
	BuddyCircle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newRadius, int newLives)
	: Circle(pge, pos, newRadius), lives(newLives){}


	void draw(const olc::Pixel& color) override {
		if(alive() || color == olc::WHITE){
			// Draw the circle
			pixelGameEngine->FillCircle(position, radius, color);

			// Draw the amount of life
			int textScale = 2;
			std::string lives_string = std::to_string(lives);
			olc::vi2d livesStringSize = pixelGameEngine->GetTextSize(lives_string);
			pixelGameEngine->DrawString(position.x - textScale * (livesStringSize.x / 2), position.y, lives_string, color == olc::WHITE ? olc::WHITE : olc::GREY, textScale);
		}
	}
	void clear() override {
		draw(olc::WHITE);
	}	

	bool alive(){
		return lives > 0;
	}

	void kill(){
		lives = 0;
	}

	void moveToCircle(Circle& c, int pixels){
		if(!circleCircleCollision(c, *this))
			moveToPos(c.getPosition(), pixels);
	}
	void moveToPos(const olc::vi2d& pos, int pixels){
		moveToCord(pos.x, pos.y, pixels);
	}
	void moveToCord(int x, int y, int pixels){
		movePosition(olc::vi2d( x<position.x ? -pixels : pixels, y<position.y ? -pixels : pixels ));
	}

	void addLife(int amount){
		lives += amount;
	}

	void subtractLife(int amount){
		if(alive()){
			lives -= amount;
			// If it dies
			if(!alive()){
				setRadius(0);
			}
		}
	}

	void grow(int amount){
		if(getRadius() < 50){
			addRadius(amount);
		}
	}
};

#endif