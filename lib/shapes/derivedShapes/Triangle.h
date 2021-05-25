#ifndef TRIANGLE
#define TRIANGLE

#include "..\Shape.h"

#define SQRT3 97 / 56
#define RECSQRT3 56 / 97
class Triangle : public Shape{
	int height;

private:
	olc::vi2d topPoint(){ return position + olc::vi2d(0, -(height * 2) / 3); }
	olc::vi2d botLeftPoint(){ return position + olc::vi2d(-height * RECSQRT3, height / 3); }
	olc::vi2d botRightPoint(){ return position + olc::vi2d(height * RECSQRT3, height / 3); }


public:
	Triangle()
	: Shape(), height(0){}
	Triangle(olc::PixelGameEngine& pge)
	: Shape(pge), height(0){}
	Triangle(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), height(0){}
	Triangle(olc::PixelGameEngine& pge, olc::vi2d& pos, int newHeight)
	: Shape(pge, pos), height(newHeight){}

	void draw(const olc::Pixel& color){
		pixelGameEngine->FillTriangle(topPoint(), botLeftPoint(), botRightPoint(), color);
	}

	void clear(){
		pixelGameEngine->FillTriangle(topPoint(), botLeftPoint(), botRightPoint(), olc::WHITE);
	}

	void setHeight(int h){ height = h; }
	void addHeight(int h){ height += h; }
	int getHeight(){ return height; }
};

#endif