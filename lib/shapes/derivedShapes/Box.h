#ifndef BOX_H
#define BOX_H

class Box: public Square{
protected:
	virtual void draw(const olc::Pixel& colorToDraw) override{
		pixelGameEngine->DrawRect(getTopLeftPoint(), olc::vi2d(length, length), colorToDraw);
	}

public:
	Box()
	: Square(){}
	Box(olc::PixelGameEngine& pge)
	: Square(pge){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Square(pge, pos){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed)
	: Square(pge, pos, _speed){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color)
	: Square(pge, pos, _speed, _color){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos, int _speed, const olc::Pixel& _color, int newLength)
	: Square(pge, pos, _speed, _color, newLength){}

	virtual void draw(){
		draw(color);
	}
	
	// Moving ---
	virtual void move(int pixels) = 0;
};

#endif