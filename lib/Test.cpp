// 
// Base shape class
// 
class Shape{
protected:
	olc::PixelGameEngine* pixelGameEngine;
	olc::vi2d position;
	olc::Pixel color;

	virtual void draw(const olc::Pixel& colorToDraw) = 0;

public:
	void draw(){
		draw(color);
	}

};

// 
// Circle class
// 
class Circle : public Shape{
protected:
	int radius;

	virtual void draw(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillCircle(position, radius, colorToDraw);
	}

public:
};

// 
// MainCircle class
// 
class MainCircle: public Circle{
protected:
	// Drawing
	void draw(const olc::Pixel& colorToDraw) override {
		pixelGameEngine->FillCircle(position, radius, colorToDraw);
	}

public:
};

// 
// Driver
// 
int main(){
	MainCircle mainCircle = MainCircle();
	mainCircle.draw();
}