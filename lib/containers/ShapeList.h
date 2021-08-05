#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "../Direction.h"
#include "../ShapeType.h"
#include "./AnimationContainer.h"

class ShapeList{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	AnimationContainer* animationContainer;

	ShapeType shapeType;

	virtual void make(olc::vi2d _loc, Direction dirCode) = 0;

public:
	ShapeList()
	: pixelGameEngine(nullptr), animationContainer(nullptr){}
	ShapeList(int typeCode)
	: pixelGameEngine(nullptr), animationContainer(nullptr){}
	ShapeList(olc::PixelGameEngine& pge, AnimationContainer& ac, ShapeType typeCode)
	: pixelGameEngine(&pge), animationContainer(&ac), shapeType(typeCode){}

	bool isEnemy(){ return shapeType == ShapeType::ENEMY; }

	// Direction code tells the direction where the circle is comming from on the screen
	// It is a bitwise code, so:
	// 0000 0000 <- from right to left, if the bit is a 1 it means:
	// - From Top
	// - From Bottom
	// - From Left
	// - From Right
	// - From Top Left
	// - From Top Right
	// - Form Bottom Left
	// - From Bottom Right
	// If multiple bits are one, them multiple circles will pop out
	virtual void add(uint8_t dirFromCode){
		if(dirFromCode & 0x01){ // FROM TOP
			make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), Direction::DOWN);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), Direction::UP);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			make(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), Direction::RIGHT);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			make(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), Direction::LEFT);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), Direction::DOWNRIGHT);
			}else{ // FROM LEFT ON TOP HALF
				make(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), Direction::DOWNRIGHT);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				make(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), Direction::DOWNLEFT);
			}else{ // FROM RIGHT ON TOP HALF
				make(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), Direction::DOWNLEFT);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), Direction::UPRIGHT);
			}else{ // FROM LEFT ON BOTTOM HALF
				make(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), Direction::UPRIGHT);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				make(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), Direction::UPLEFT);
			}else{ // FROM RIGHT ON BOTTOM HALF
				make(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), Direction::UPLEFT);
			}
		}
	}


	virtual void deleteAll() = 0;
	virtual void hideAll() = 0;
	virtual void drawAll() = 0;
	virtual void moveAll() = 0;
	virtual int checkCollisionsWith(ShapeList& list, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(Circle& c, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(Flower& f, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(Line& l, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(Square& s, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(Triangle& t, bool removeOnCollision = true) = 0;
	virtual int checkCollisionsWith(MainCircle& mc, bool removeOnCollision = true) = 0;
};

#endif