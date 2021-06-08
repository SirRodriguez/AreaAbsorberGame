#ifndef BUDDYCIRCLE_H
#define BUDDYCIRCLE_H

#include "..\utils.h"
#include "..\shapes\derivedShapes\Circle.h"

class BuddyCircle: public Circle{
	MainCircle* shapeToFollow;

protected:
	int lives;

	// Internal movements
	void moveToCord(int x, int y, int pixels){
		movePosition(olc::vi2d( x<position.x ? -pixels : pixels, y<position.y ? -pixels : pixels ));
	}
	void moveToPos(const olc::vi2d& pos, int pixels){
		moveToCord(pos.x, pos.y, pixels);
	}

public:
	BuddyCircle()
	: Circle(), lives(0), shapeToFollow(nullptr){}
	BuddyCircle(olc::PixelGameEngine& pge)
	: Circle(pge), lives(0), shapeToFollow(nullptr){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow)
	: Circle(pge), lives(0), shapeToFollow(&_shapeToFollow){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow, olc::vi2d& pos)
	: Circle(pge, pos), lives(0), shapeToFollow(&_shapeToFollow){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow, olc::vi2d& pos, int _speed)
	: Circle(pge, pos, _speed), lives(0), shapeToFollow(&_shapeToFollow){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Circle(pge, pos, _speed, _color), lives(0), shapeToFollow(&_shapeToFollow){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius)
	: Circle(pge, pos, _speed, _color, newRadius), lives(0), shapeToFollow(&_shapeToFollow){}
	BuddyCircle(olc::PixelGameEngine& pge, MainCircle& _shapeToFollow, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives)
	: Circle(pge, pos, _speed, _color, newRadius), lives(newLives), shapeToFollow(&_shapeToFollow){}


	// Drawing ---
	void draw(const olc::Pixel& colorToDraw) override {
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

	// Life ---
	bool alive(){
		return lives > 0;
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
	void move(int pixels) override {
		if(!circleCircleCollision(*shapeToFollow, *this)){
			moveToPos(shapeToFollow->getPosition(), pixels);
		}
	}

	// Size ---
	void grow(int amount){
		if(getRadius() < 50){
			addRadius(amount);
		}
	}
};

#endif