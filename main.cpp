#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>
#include <map>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <cmath>

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
	bool moveShapesDown;

	// Variables
	olc::vi2d mainCirclePos;
	int mainCircleRadius;

	// Other shapes containers
	struct shapesContainer{
		int id;
		std::map<int, std::pair<olc::vi2d, int>> otherCircle; // key = id, value = location, radius
		int maxRadius;
		void initialize(){
			id = 0;
			otherCircle.clear();
			maxRadius = 50;
		}
		void drawShapes(AreaAbsorber& aa){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				aa.FillCircle(it->second.first, it->second.second, olc::RED);
			}
		}
		void addShape(AreaAbsorber& aa){
			olc::vi2d loc = olc::vi2d(rand() % aa.ScreenWidth(), 0);
			int radius = rand() % maxRadius;
			otherCircle[id] = std::make_pair(loc, radius);
			++id;
		}
		void moveShapes(AreaAbsorber& aa){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				it->second.first += olc::vi2d(0, 1);
				// if it reaches the bottom, delete it
				int pos = it->second.first.y;
				if(pos == aa.ScreenHeight()){
					deleteShape(it->first);
				}
			}
		}
		void deleteShape(int shapeId){
			otherCircle.erase(shapeId);
		}

		// Returns true if the collision destroyed the circle
		bool checkCollision(olc::vi2d pos, int& radius){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				// Get the distances
				int32_t x = it->second.first.x;
				int32_t y = it->second.first.y;
				double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) );

				// check if distance is less or equal the two radius combined
				if(distance <= it->second.second + radius){
					if(it->second.second > radius){
						return true;
					}else{
						deleteShape(it->first);
						// Add the smaller circle to the main Circle
						radius += it->second.second / 10;
					}
				}
			}

			return false;
		}
	};
	shapesContainer shapesContainer;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

	void setMainMenu(){
		// Make a text saying to press space bar to start in the center of the screen
		const int scale = 4;

		const std::string press = "Press";
		olc::vi2d pressSize = GetTextSize(press);
		const std::string space = "SPACE";
		olc::vi2d spaceSize = GetTextSize(space);
		const std::string to = "to";
		olc::vi2d toSize = GetTextSize(to);
		const std::string start = "start!";
		olc::vi2d startSize = GetTextSize(start);

		DrawString(// Press
			ScreenWidth() / 2 - scale * (pressSize.x / 2), 
			ScreenHeight() / 2 - scale * (pressSize.y + spaceSize.y + 2), 
			press, 
			olc::BLACK,
			scale
		);
		DrawString(// SPACE
			ScreenWidth() / 2 - scale * (spaceSize.x / 2), 
			ScreenHeight() / 2 - scale * (spaceSize.y), 
			space, 
			olc::BLACK,
			scale
		);
		DrawString(// To
			ScreenWidth() / 2 - scale * (toSize.x / 2), 
			ScreenHeight() / 2 + scale * (2), 
			to, 
			olc::BLACK,
			scale
		);
		DrawString(// Start!
			ScreenWidth() / 2 - scale * (startSize.x / 2), 
			ScreenHeight() / 2 + scale * (toSize.y + 2), 
			start, 
			olc::BLACK,
			scale
		);
	}

	void initializeGame(){
		// Set flags
		inMainMenu = true;
		moveShapesDown = false;

		// Initialize the random seed
		srand(time(0));

		// Initialize the struct
		shapesContainer.initialize();

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

		// Set main circle position to middle and its defualt radius
		mainCirclePos = olc::vi2d(ScreenWidth() / 2, ScreenHeight() / 2);
		mainCircleRadius = 10;
	}

	void checkUserInput(){
		// Get the up, down, left, right buttons
		upButton = GetKey(olc::Key::UP);
		downButton = GetKey(olc::Key::DOWN);
		leftButton = GetKey(olc::Key::LEFT);
		rightButton = GetKey(olc::Key::RIGHT);

		// Update the position of the circle
		if(upButton.bHeld){
			if(mainCirclePos.y > 0){
				mainCirclePos -= olc::vi2d(0, 1);
			}
		}
		if(downButton.bHeld){
			if(mainCirclePos.y < ScreenHeight()){
				mainCirclePos += olc::vi2d(0, 1);
			}
		}
		if(leftButton.bHeld){
			if(mainCirclePos.x > 0){
				mainCirclePos -= olc::vi2d(1, 0);
			}
		}
		if(rightButton.bHeld){
			if(mainCirclePos.x < ScreenWidth()){
				mainCirclePos += olc::vi2d(1, 0);
			}
		}
	}


public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here

		initializeGame();

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
			checkUserInput();

			// Generate shape if needed
			const int likelyHood = 200;
			if(rand() % likelyHood == 0){ // If likely then make a shape
				shapesContainer.addShape(*this);
			}

			// Move the shapes every other frame
			if(moveShapesDown){
				shapesContainer.moveShapes(*this);
			}
			moveShapesDown = !moveShapesDown;

			// Collision detection
			if(shapesContainer.checkCollision(mainCirclePos, mainCircleRadius)){
				// Back to main menu and end the game
				initializeGame();
			}

			// Clear and update the circle position
			Clear(olc::WHITE);
			FillCircle(mainCirclePos, mainCircleRadius, olc::BLUE);
			shapesContainer.drawShapes(*this);
		}

		// Check the escape button to end the program
		escButton = GetKey(olc::Key::ESCAPE);
		if(escButton.bPressed){
			if(inMainMenu){
				olc_Terminate();
			}else{
				// Go back to main menu
				initializeGame();
			}
		}

		return true;
	}
};

int main(){
	AreaAbsorber aa;
	if(aa.Construct(750, 1000, 1, 1))
		aa.Start();

	return 0;
}