#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Shape.h"

#define SQRT3 97 / 56
#define RECSQRT3 56 / 97
class Triangle : public Shape{
protected:
	olc::Decal* triangleDecal;
	int height;

public:
	Triangle(olc::PixelGameEngine& pge, AnimationContainer& ac, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newHeight)
	: Shape(pge, ac, pos, _speed, _color), height(newHeight), triangleDecal(new olc::Decal(whiteEquilateralTriangleSprite)){}

	virtual ~Triangle(){
		if(triangleDecal != nullptr) delete triangleDecal;
	}

	// Drawing ---
	virtual void draw() override {
		olc::vf2d positionVector = { float(position.x), float(position.y) };
		olc::vf2d offset = { (whiteEquilateralTriangleWidth * whiteEquilateralTriangleScaleToOneHeight * height) / 2, (whiteEquilateralTriangleHeight * whiteEquilateralTriangleScaleToOneHeight * height) / 2 };
		pixelGameEngine->DrawDecal(positionVector - offset, triangleDecal, { whiteEquilateralTriangleScaleToOneHeight * height, whiteEquilateralTriangleScaleToOneHeight * height }, color);
	}
	
	// Moving ---
	virtual void move() = 0;

	// Height ---
	void setHeight(int h){ height = h; }
	void addHeight(int h){ height += h; }
	int getHeight(){ return height; }

	// Points ---
	olc::vi2d topPoint(){ return position + olc::vi2d(0, -(height * 2) / 3); }
	olc::vi2d botLeftPoint(){ return position + olc::vi2d(-height * RECSQRT3, height / 3); }
	olc::vi2d botRightPoint(){ return position + olc::vi2d(height * RECSQRT3, height / 3); }
};

#endif