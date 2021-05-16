#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>

// Command to compile 
// g++ -o main.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class AreaAbsorber : public olc::PixelGameEngine {
	// Keys to use in play
	olc::HWButton spaceButton;
	olc::HWButton upButton;
	olc::HWButton downButton;
	olc::HWButton leftButton;
	olc::HWButton rightButton;
	olc::HWButton escButton;

	// flags
	bool inMainMenu;

	// Variables
	olc::vi2d mainCirclePos;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

	void setMainMenu(){
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

		// Set flags
		inMainMenu = true;
	}


public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here

		// Make the background white
		Clear(olc::WHITE);

		// Make a middle horizontal and vertical line for debugging
		// int32_t middleX = ScreenWidth() / 2;
		// int32_t middleY = ScreenHeight() / 2;
		// for(int x = 0; x < ScreenWidth(); ++x){
		// 	Draw(x, middleY, olc::RED);
		// }
		// for(int y = 0; y < ScreenHeight(); ++y){
		// 	Draw(middleX, y, olc::RED);
		// }

		setMainMenu();

		// Set main circle position to middle
		mainCirclePos = olc::vi2d(ScreenWidth() / 2, ScreenHeight() / 2);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// Called Once per frame

		if(inMainMenu){
			spaceButton = GetKey(olc::Key::SPACE);
			if(spaceButton.bPressed){
				Clear(olc::WHITE);
				FillCircle(mainCirclePos, 3, olc::BLUE);
				inMainMenu = false;
			}
		}else{
			// Get the up, down, left, right buttons
			upButton = GetKey(olc::Key::UP);
			downButton = GetKey(olc::Key::DOWN);
			leftButton = GetKey(olc::Key::LEFT);
			rightButton = GetKey(olc::Key::RIGHT);

			// Update the position of the circle
			if(upButton.bHeld){
				mainCirclePos -= olc::vi2d(0, 1);
			}
			if(downButton.bHeld){
				mainCirclePos += olc::vi2d(0, 1);
			}
			if(leftButton.bHeld){
				mainCirclePos -= olc::vi2d(1, 0);
			}
			if(rightButton.bHeld){
				mainCirclePos += olc::vi2d(1, 0);
			}

			// Clear and update the circle position
			Clear(olc::WHITE);
			FillCircle(mainCirclePos, 10, olc::BLUE);
		}

		// Check the escape button to end the program
		escButton = GetKey(olc::Key::ESCAPE);
		if(escButton.bPressed){
			olc_Terminate();
		}

		return true;
	}
};

int main(){
	AreaAbsorber aa;
	if(aa.Construct(500, 1000, 1, 1))
		aa.Start();

	return 0;
}