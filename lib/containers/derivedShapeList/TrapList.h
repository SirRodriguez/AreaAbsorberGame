#ifndef TRAPLIST_H
#define TRAPLIST_H

#include "../ShapeList.h"
#include "../../objects/Trap.h"

#define ENEMYCODE 0

class TrapList: public ShapeList{
protected:
	std::list<Trap> traps;

	virtual void make(olc::vi2d _loc, int dirCode) override {
		const olc::Pixel trapColor = olc::BLUE;
		const uint8_t trapSpeed = 4;
		const uint8_t trapLength = 40;

		traps.push_back(Trap(*pixelGameEngine, _loc, trapSpeed, trapColor, trapLength, dirCode));

	}

public:
	TrapList()
	: ShapeList(ENEMYCODE){}
	TrapList(olc::PixelGameEngine& pge)
	: ShapeList(pge, ENEMYCODE){}

	virtual void deleteAll() override {
		traps.clear();
	}

	virtual void hideAll() override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->clear();
		}
	}

	virtual void drawAll() override {
		for(auto it = traps.begin(); it != traps.end(); ++it){
			it->draw();
		}
	}

	virtual void moveAll() override {
		for(auto it = traps.begin(); it != traps.end();){
			it->move();
			if(it->outOfBounds()){
				traps.erase(it++);
			}else{
				++it;
			}
		}
	}

	virtual int checkCollisionsWith(Circle& c){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(circleSquareCollision(c, *it)){
				int dirCode = it->getDirectionCode();
				traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Flower& f){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(squareFlowerCollision(*it, f)){
				int dirCode = it->getDirectionCode();
				traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

	virtual int checkCollisionsWith(Line& l){
		for(auto it = traps.begin(); it != traps.end(); ++it){
			if(lineSquareCollision(l, *it)){
				int dirCode = it->getDirectionCode();
				traps.erase(it);
				return dirCode;
			}
		}

		return 0;
	}

};

#endif