#ifndef SHAPE
#define SHAPE

class Shape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	int area;

public:
	Shape(){}
	Shape(olc::PixelGameEngine& pge){
		pixelGameEngine = &pge;
	}
	// Shape(olc::PixelGameEngine& pge, olc::vi2d& pos){
	// 	pixelGameEngine = &pge;
	// 	position = pos;
	// }

	bool belowTopOfScreen(){ return position.y > 0; }
	bool aboveBottomOfScreen(){ return position.y < pixelGameEngine->ScreenHeight(); }
	bool rightOfLeftOfScreen(){ return position.x > 0; }
	bool leftOfRightOfScreen(){ return position.x < pixelGameEngine->ScreenWidth(); }

	void setPosition(olc::vi2d point){ position = point; }
	void movePosition(olc::vi2d otherPoint){ position += otherPoint; }
	olc::vi2d& getPosition(){ return position; }

	void setArea(int a){ area = a; }
	void addArea(int a){ area += a; }
	int getArea(){ return area; }

	virtual void draw(const olc::Pixel& color) = 0;
	virtual void clear() = 0;
};

#endif