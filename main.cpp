#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>

// Command to compile 
// g++ -o main.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class AreaAbsorber : public olc::PixelGameEngine {
public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here

		// Make the background white
		Clear(olc::WHITE);

		// Make a middle horizontal and vertical line for debugging
		int32_t middleX = ScreenWidth() / 2;
		int32_t middleY = ScreenHeight() / 2;
		for(int x = 0; x < ScreenWidth(); ++x){
			Draw(x, middleY, olc::RED);
		}
		for(int y = 0; y < ScreenHeight(); ++y){
			Draw(middleX, y, olc::RED);
		}


		// Make a text saying to press space bar to start
		const std::string press = "Press";
		olc::vi2d pressSize = GetTextSize(press);
		const std::string space = "SPACE";
		olc::vi2d spaceSize = GetTextSize(space);
		const std::string to = "to";
		olc::vi2d toSize = GetTextSize(to);
		const std::string start = "start!";
		olc::vi2d startSize = GetTextSize(start);

		DrawString(// Press
			ScreenWidth() / 2 - pressSize.x / 2, 
			ScreenHeight() / 2 - pressSize.y - spaceSize.y - 2, press, 
			olc::BLACK
		);
		DrawString(// SPACE
			ScreenWidth() / 2 - spaceSize.x / 2, 
			ScreenHeight() / 2 - spaceSize.y, 
			space, 
			olc::BLACK
		);
		DrawString(// To
			ScreenWidth() / 2 - toSize.x / 2, 
			ScreenHeight() / 2 + 2, 
			to, 
			olc::BLACK
		);
		DrawString(// Start!
			ScreenWidth() / 2 - startSize.x / 2, 
			ScreenHeight() / 2 + toSize.y + 2, 
			start, 
			olc::BLACK
		);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// Called Once per frame

		// for (int x = 0; x < ScreenWidth(); x++)
		// 	for (int y = 0; y < ScreenHeight(); y++)
		// 		Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));

		return true;
	}
};

int main(){
	AreaAbsorber aa;
	if(aa.Construct(90, 180, 4, 4))
		aa.Start();

	return 0;
}