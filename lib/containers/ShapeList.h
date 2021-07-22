#ifndef SHAPELIST_H
#define SHAPELIST_H

#define ENEMYCODE 0
#define BUDDYCODE 1
#define POWERUPCODE 2
#define MAINCIRCLECODE 3

class ShapeList{
private:
	enum ShapeType{
		ENEMY,
		BUDDY,
		POWERUP,
		MAINCIRCLE
	};

	void assignShapeType(int typeCode){
		switch(typeCode){
			case ENEMYCODE: shapeType = ShapeType::ENEMY; break;
			case BUDDYCODE: shapeType = ShapeType::BUDDY; break;
			case POWERUPCODE: shapeType = ShapeType::POWERUP; break;
			case MAINCIRCLECODE: shapeType = ShapeType::MAINCIRCLE; break;
			default: shapeType = ShapeType::ENEMY; break;
		}
	}

protected:
	olc::PixelGameEngine* pixelGameEngine;

	ShapeType shapeType;

	virtual void make(olc::vi2d _loc, int dirCode) = 0;

public:
	ShapeList()
	: pixelGameEngine(nullptr){}
	ShapeList(int typeCode)
	: pixelGameEngine(nullptr){
		assignShapeType(typeCode);
	}
	ShapeList(olc::PixelGameEngine& pge, int typeCode)
	: pixelGameEngine(&pge){
		assignShapeType(typeCode);
	}

	int getType(){
		switch(shapeType){
			case ShapeType::ENEMY: return ENEMYCODE;
			case ShapeType::BUDDY: return BUDDYCODE;
			case ShapeType::POWERUP: return POWERUPCODE;
			case ShapeType::MAINCIRCLE: return MAINCIRCLECODE;
			default: return ENEMYCODE;
		}
	}

	bool isEnemy(){
		return getType() == ENEMYCODE;
	}

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
			make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), 0), 1);
		}

		if(dirFromCode & 0x02){ // FROM BOTTOM
			make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth(), pixelGameEngine->ScreenHeight()), 0);
		}

		if(dirFromCode & 0x04){ // FROM LEFT
			make(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight()), 3);
		}

		if(dirFromCode & 0x08){ // FROM RIGHT
			make(olc::vi2d(pixelGameEngine->ScreenWidth(), rand() % pixelGameEngine->ScreenHeight()), 2);
		}

		if(dirFromCode & 0x10){ // FROM TOP LEFT
			if(rand() % 2 == 0){ // FROM TOP ON LEFT HALF
				make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, 0), 7);
			}else{ // FROM LEFT ON TOP HALF
				make(olc::vi2d(0, rand() % pixelGameEngine->ScreenHeight() / 2), 7);
			}
		}

		if(dirFromCode & 0x20){ // FROM TOP RIGHT
			if(rand() % 2 == 0){ // FROM TOP ON RIGHT HALF
				make(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2 ) + pixelGameEngine->ScreenWidth() / 2, 0), 6);
			}else{ // FROM RIGHT ON TOP HALF
				make(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2 )), 6);
			}
		}

		if(dirFromCode & 0x40){ // FROM BOTTOM LEFT
			if(rand() % 2 == 0){ // FROM BOTTOM ON LEFT HALF
				make(olc::vi2d(rand() % pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 5);
			}else{ // FROM LEFT ON BOTTOM HALF
				make(olc::vi2d(0, (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 5);
			}
		}

		if(dirFromCode & 0x80){ // FROM BOTTOM RIGHT
			if(rand() % 2 == 0){ // FROM BOTTOM ON RIGHT HALF
				make(olc::vi2d((rand() % pixelGameEngine->ScreenWidth() / 2) + pixelGameEngine->ScreenWidth() / 2, pixelGameEngine->ScreenHeight()), 4);
			}else{ // FROM RIGHT ON BOTTOM HALF
				make(olc::vi2d(pixelGameEngine->ScreenWidth(), (rand() % pixelGameEngine->ScreenHeight() / 2) + pixelGameEngine->ScreenHeight() / 2), 4);
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