#ifndef BUDDYCIRCLE_H
#define BUDDYCIRCLE_H

#include "../../Direction.h"
#include "../../shapes/derivedShapes/Circle.h"

// Forward declaration for this function only
bool circleCircleCollision(Circle& c, Circle& c2);

#define MAXRADIUS 50

class BuddyCircle: public Circle{
protected:
	int lives;

	void createHoveringTextAnimation(std::string text, Direction dir){
		int numFrames = 60;
		int dist = 50;
		int scale = 2;

		olc::vi2d pos;
		switch(dir){
			case Direction::UP: pos = position + olc::vi2d(0, -getRadius()); break;
			case Direction::DOWN: pos = position + olc::vi2d(0, getRadius()); break;
			case Direction::LEFT: pos = position + olc::vi2d(-getRadius(), 0); break;
			case Direction::RIGHT: pos = position + olc::vi2d(getRadius(), 0); break;
			case Direction::UPLEFT: pos = position + olc::vi2d(-getRadius(), -getRadius()); break;
			case Direction::UPRIGHT: pos = position + olc::vi2d(getRadius(), -getRadius()); break;
			case Direction::DOWNLEFT: pos = position + olc::vi2d(-getRadius(), getRadius()); break;
			case Direction::DOWNRIGHT: pos = position + olc::vi2d(getRadius(), getRadius()); break;
			default: pos = position; break;
		}
		animationContainer->addHoveringTextAnimation(*pixelGameEngine, pos, numFrames, color, text, dist, scale, dir);
	}

public:
	BuddyCircle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newRadius, int newLives)
	: Circle(pge, ac, pos, _speed, _color, newRadius), lives(newLives){}

	// Drawing ---
	void draw() override {
		if(alive()){
			// Draw the circle
			olc::vf2d positionVector = { float(position.x), float(position.y) };
			olc::vf2d offset = { (whiteCirclePixelWidth * whiteCircleScaleToOneRadius * radius) / 2, (whiteCirclePixelHeight * whiteCircleScaleToOneRadius * radius) / 2 };
			pixelGameEngine->DrawDecal(positionVector - offset, circleDecal, { whiteCircleScaleToOneRadius * radius, whiteCircleScaleToOneRadius * radius }, color);

			// Draw the amount of life
			int textScale = 2;
			std::string lives_string = std::to_string(lives);
			olc::vi2d livesStringSize = pixelGameEngine->GetTextSize(lives_string);

			float posx = float(position.x - textScale * (livesStringSize.x / 2));
			float posy = float(position.y);
			const olc::vf2d stringPos = olc::vf2d(posx, posy);
			const olc::Pixel textColor = olc::GREY;
			olc::vf2d scale = olc::vf2d(1.0f, 1.0f) * textScale;
			pixelGameEngine->DrawStringDecal(
				stringPos,
				lives_string,
				textColor,
				scale
			);
		}
	}

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
		createHoveringTextAnimation("+" + std::to_string(amount), Direction::UP);
		lives += amount;
	}
	void subtractLife(int amount){
		createHoveringTextAnimation("-" + std::to_string(amount), Direction::DOWN);

		if(alive()){
			lives -= amount;
			// If it dies
			if(notAlive()){
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