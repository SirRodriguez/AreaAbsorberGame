#ifndef BUDDYCIRCLE_H
#define BUDDYCIRCLE_H

#include "../../shapes/derivedShapes/Circle.h"

// Forward declaration for this function only
bool circleCircleCollision(Circle& c, Circle& c2);

#define MAXRADIUS 50

class BuddyCircle: public Circle{
protected:
	int lives;

	// Internal movements
	void moveToCord(int x, int y, int pixels){
		movePosition(olc::vi2d( x < position.x ? -pixels : pixels, y < position.y ? -pixels : pixels ));
	}
	void moveToPos(const olc::vi2d& pos, int pixels){
		moveToCord(pos.x, pos.y, pixels);
	}

	// Drawing ---
	void drawWithColor(const olc::Pixel& colorToDraw) override {
		if(alive() || colorToDraw == olc::WHITE){
			// Draw the circle
			pixelGameEngine->FillCircle(position, radius, colorToDraw);

			// Draw the amount of life
			int textScale = 2;
			std::string lives_string = std::to_string(lives);
			olc::vi2d livesStringSize = pixelGameEngine->GetTextSize(lives_string);
			pixelGameEngine->DrawString(position.x - textScale * (livesStringSize.x / 2), position.y, lives_string, colorToDraw == olc::WHITE ? olc::WHITE : olc::GREY, textScale);
		}
	}

public:
	BuddyCircle()
	: Circle(), lives(0){}
	BuddyCircle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives)
	: Circle(pge, ac, pos, _speed, _color, newRadius), lives(newLives){}

	// Life ---
	bool alive(){
		return lives > 0;
	}
	bool notAlive(){
		return !alive();
	}
	void kill(){
		lives = 0;
		setRadius(0);
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

	// Moving ---
	void move(Circle& c){
		if(alive()){
			if(!circleCircleCollision(c, *this)){
				moveToPos(c.getPosition(), speed);
			}
		}
	}

	void move() override {
		// Move to center. Need a shape to follow.
		olc::vi2d center = olc::vi2d(pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight() / 2);
		moveToPos(center, speed);
	}

	// Size ---
	void grow(int amount){
		if(getRadius() < MAXRADIUS){
			addRadius(amount);

			if(getRadius() > MAXRADIUS){
				setRadius(MAXRADIUS);
			}
		}
	}
};

#endif