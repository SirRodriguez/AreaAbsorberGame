#ifndef FLOWER_H
#define FLOWER_H

#include "../Circle.h"
#include "Pedal.h"


class Flower: public Circle{
protected:
	std::vector<Pedal> pedals;
	int numPedals;
	double degOffset;

	// Pedal Radius
	int getPedalRadius(int r){ return r / 2; }
	int getPedalRadius(){ return getPedalRadius(getRadius()); }

	virtual olc::vi2d getLocationOffsetFromDeg(double d){
		int r = getRadius() + getPedalRadius();
		int x = r * std::cos(d * PI() / 180);
		int y = r * std::sin(d * PI() / 180);

		return olc::vi2d(x, y);
	}

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override{
		pixelGameEngine->FillCircle(position, radius, colorToDraw);

		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			if(colorToDraw == olc::WHITE){
				it->clear();
			}else{
				it->draw();
			}
		}
	}

	virtual void fixPedalsToPosition(){
		if(numPedals > 0){
			double increment = 360 / numPedals;
			double deg = increment + degOffset;	

			for(auto it = pedals.begin(); it != pedals.end(); ++it){
				olc::vi2d locOffset = getLocationOffsetFromDeg(deg);
				olc::vi2d loc = position + locOffset;
				it->setPosition(loc);
				deg += increment;
			}
		}
	}

public:
	Flower()
	: Circle(){}
	Flower(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, const olc::Pixel& _pedalColor, int newRadius, int _numPedals, double _degOffset)
	: Circle(pge, pos, _speed, _color, newRadius), numPedals(_numPedals), degOffset(_degOffset){
		if(numPedals > 0){
			double increment = 360 / numPedals;
			double deg = increment + degOffset;

			for(int i = 0; i < numPedals; ++i){
				olc::vi2d locOffset = getLocationOffsetFromDeg(deg);
				olc::vi2d loc = pos + locOffset;
				pedals.push_back(Pedal(pge, loc, _speed, _pedalColor, getPedalRadius()));
				deg += increment;
			}
		}
	}

	// Moving
	virtual void move() = 0;

	// Pedals
	virtual std::vector<Pedal>& getPedals(){ return pedals; }

	// growing
	virtual void setRadius(int r) override {
		radius = r;
		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			it->setRadius(getPedalRadius(r));
		}
	}
	virtual void addRadius(int r) override {
		radius += r;
		for(auto it = pedals.begin(); it != pedals.end(); ++it){
			it->addRadius(getPedalRadius(r));
		}
	}

};

#endif