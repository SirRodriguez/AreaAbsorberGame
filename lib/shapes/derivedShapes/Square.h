#ifndef SQUARE_H
#define SQUARE_H

class Square: public Shape{
protected:
	int length;

public:
	Square()
	: Shape(), length(0){}
	Square(olc::PixelGameEngine& pge)
	: Shape(pge), length(0){}
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), length(0){}
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Shape(pge, pos, _speed), length(0){}
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Shape(pge, pos, _speed, _color), length(0){}
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Shape(pge, pos, _speed, _color), length(newLength){}

	// Drawing ---
	virtual void draw(const olc::Pixel& colorToDraw){
		pixelGameEngine->FillRect(getTopLeftPoint(), olc::vi2d(length, length), colorToDraw);
	}
	virtual void clear(){
		draw(olc::WHITE);
	}

	// Moving ---
	virtual void move(int pixels) = 0;

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