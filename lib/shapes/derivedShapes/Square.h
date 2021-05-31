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
	Square(olc::PixelGameEngine& pge, olc::vi2d& pos, int newLength)
	: Shape(pge, pos), length(newLength){}

	void draw(const olc::Pixel& color){
		pixelGameEngine->FillRect(getTopLeftPoint(), olc::vi2d(length, length), color);
	}
	void clear(){
		draw(olc::WHITE);
		// pixelGameEngine->FillRect(getTopLeftPoint(), olc::vi2d(length, length), olc::WHITE);
	}

	void setLength(int l){ length = l; }
	void addLength(int l){ length += l; }
	int getLength(){ return length; }

	olc::vi2d getTopLeftPoint(){ return position + olc::vi2d(-length / 2, -length / 2); }
	olc::vi2d getTopRightPoint(){ return position + olc::vi2d(length / 2, -length / 2); }
	olc::vi2d getBotLeftPoint(){ return position + olc::vi2d(-length / 2, length / 2); }
	olc::vi2d getBotRightPoint(){ return position + olc::vi2d(length / 2, length / 2); }
};

#endif