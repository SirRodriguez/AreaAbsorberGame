#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>

// Command to compile 
// g++ -o main.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class ComplexVisualizer : public olc::PixelGameEngine {
public:
	ComplexVisualizer(){
		sAppName = "ComplexVisualizer";
	}

public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here

		// Make the background white
		Clear(olc::WHITE);

		// Make a 

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// Called Once per frame

		// for (int x = 0; x < ScreenWidth(); x++)
		// 	for (int y = 0; y < ScreenHeight(); y++)
		// 		Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));


		std::cout << fElapsedTime << std::endl;

		return true;
	}
};

int main(){
	ComplexVisualizer cv;
	if(cv.Construct(250, 500, 4, 4, true))
		cv.Start();

	return 0;
}