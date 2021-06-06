#ifndef BOX_H
#define BOX_H

class Box: public Square{
public:
	Box()
	: Square(){}
	Box(olc::PixelGameEngine& pge)
	: Square(pge){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos)
	: Square(pge, pos){}
	Box(olc::PixelGameEngine& pge, olc::vi2d& pos, int newLength)
	: Square(pge, pos, newLength){}

	// Drawing ---
	void draw(const olc::Pixel& color) override{
		pixelGameEngine->DrawRect(getTopLeftPoint(), olc::vi2d(length, length), color);
	}

	void clear(){
		draw(olc::WHITE);
	}

	// Moving ---
	void move(int pixels){
		// TODO
	}
	// virtual void move(int pixels) = 0;
};

#endif