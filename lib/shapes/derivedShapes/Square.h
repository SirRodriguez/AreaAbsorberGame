#ifndef SQUARE_H
#define SQUARE_H

class Square: public Shape{
protected:
	int length;

	virtual void drawWithColor(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillRect(getTopLeftPoint(), olc::vi2d(length, length), colorToDraw);
	}

public:
	Square()
	: Shape(), length(0){}
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Shape(pge, pos, _speed, _color), length(newLength){}
	
	// Moving ---
	virtual void move() = 0;

	// Lengths ---
	void setLength(int l){ length = l; }
	void addLength(int l){ length += l; }
	int getLength(){ return length; }

	// Points ---
	olc::vi2d getTopLeftPoint(){ return position + olc::vi2d(-length / 2, -length / 2); }
	olc::vi2d getTopRightPoint(){ return position + olc::vi2d(length / 2, -length / 2); }
	olc::vi2d getBotLeftPoint(){ return position + olc::vi2d(-length / 2, length / 2); }
	olc::vi2d getBotRightPoint(){ return position + olc::vi2d(length / 2, length / 2); }
};

#endif