#ifndef FLOWER_H
#define FLOWER_H

#include "../Circle.h"
#include "Pedal.h"


class Flower: public Circle{
protected:
	std::list<Pedal*> pedals;
	int numPedals;
	double degOffset;

	// Pedal Radius
	int getPedalRadius(int r){ return r / 2; }
	int getPedalRadius(){ return getPedalRadius(getRadius()); }

	olc::vi2d getLocationOffsetFromDeg(double d){
		int r = getRadius() + getPedalRadius();
		int x = r * std::cos(d * PI() / 180);
		int y = r * std::sin(d * PI() / 180);

		return olc::vi2d(x, y);
	}

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override{
		pixelGameEngine->FillCircle(position, radius, colorToDraw);

		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			if(colorToDraw == olc::WHITE){
				(*it)->clear();
			}else{
				(*it)->draw();
			}
		}
	}

	void fixPedalsToPosition(){
		if(numPedals > 0){
			double increment = 360 / numPedals;
			double deg = increment + degOffset;	

			for(auto it = pedals.begin(); it != pedals.end(); ++it){
				olc::vi2d locOffset = getLocationOffsetFromDeg(deg);
				olc::vi2d loc = position + locOffset;
				(*it)->setPosition(loc);
				deg += increment;
			}
		}
	}

	void rotateDegOffset(double deg){
		degOffset += deg;
		if(degOffset > 360.0) degOffset -= 360.0;
		if(degOffset < 0.0) degOffset += 360.0;
	}

public:
	Flower()
	: Circle(){}
	Flower(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _pedalColor, int newRadius, int _numPedals, double _degOffset)
	: Circle(pge, ac, pos, _speed, _color, newRadius), numPedals(_numPedals), degOffset(_degOffset){
		if(numPedals > 0){
			double increment = 360 / numPedals;
			double deg = increment + degOffset;

			for(int i = 0; i < numPedals; ++i){
				olc::vi2d locOffset = getLocationOffsetFromDeg(deg);
				olc::vi2d loc = pos + locOffset;
				pedals.push_back(new Pedal(pge, ac, loc, _speed, _pedalColor, getPedalRadius()));
				deg += increment;
			}
		}
	}

	~Flower(){
		for(auto it = pedals.begin(); it != pedals.end(); ++it)
			delete *it;
	}

	// Moving
	virtual void move() = 0;

	// Pedals
	virtual std::list<Pedal*>& getPedals(){ return pedals; }

	// growing
	virtual void setRadius(int r) override {
		radius = r;
		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			(*it)->setRadius(getPedalRadius(r));
		}
	}
	virtual void addRadius(int r) override {
		radius += r;
		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			(*it)->addRadius(getPedalRadius(r));
		}
	}

};

#endif