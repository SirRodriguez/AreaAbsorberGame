#ifndef LINE_H
#define LINE_H

#include "..\Shape.h"

class Line : public Shape {
	int length;

public:
	Line()
	: Shape(), length(0){}
	Line(olc::PixelGameEngine& pge)
	: Shape(pge), length(0){}
	Line(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Shape(pge, pos), length(0){}
	Line(olc::PixelGameEngine& pge, olc::vi2d& pos, int len)
	: Shape(pge, pos), length(len){}

	void draw(const olc::Pixel& color){
		// TODO
	}
	void clear(){
		// TODO
	}

	void setLength(int l){ length = l; }
	void addLength(int l){ length += l; }
	int getLength(){ return length; }

}

#endif