#ifndef AREAABSORBER
#define AREAABSORBER

// #include "olcPixelGameEngine.h"

// #include "ShapesContainer.h"

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

	// Text
	const int textScale = 4;
	// Move Speeds
	int otherShapeSpeed;
	int MainCircleSpeed;
	// Poition
	olc::vi2d mainCirclePos;
	int mainCircleRadius;
	// Score
	int score;
	int level;
	// Likelyhood of other circles generated
	int likelyHood;

	// Other shapes containers
	struct ShapesContainer{
		int id;
		std::map<int, std::pair<olc::vi2d, int>> otherCircle; // key = id, value = location, radius
		int maxRadius;

		void initialize(){
			id = 0;
			otherCircle.clear();
			maxRadius = 50;
		}

		// Iterators
		std::map<int, std::pair<olc::vi2d, int>>::iterator begin(){
			return otherCircle.begin();
		}
		std::map<int, std::pair<olc::vi2d, int>>::iterator end(){
			return otherCircle.end();
		}

		void addShape(int32_t screenWidth){
			olc::vi2d loc = olc::vi2d(rand() % screenWidth, 0);
			int radius = rand() % maxRadius;
			otherCircle[id] = std::make_pair(loc, radius);
			++id;
		}

		void moveShapes(int32_t screenHeight, int pixels){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				it->second.first += olc::vi2d(0, pixels);
				// if it reaches the bottom, delete it
				int pos = it->second.first.y;
				if(pos == screenHeight){
					deleteShape(it->first);
				}
			}
		}

		void deleteShape(int shapeId){
			otherCircle.erase(shapeId);
		}

		void deleteAllShapes(){
			otherCircle.clear();
		}

		// return 0 if no collision
		// return -1 if other circle is bigger
		// return any positive number means that the circle was smaller and thats the size
		int checkCollision2(const olc::vi2d& pos, const int& radius){
			for(auto it = otherCircle.begin(); it != otherCircle.end(); ++it){
				// Get the distances
				int32_t x = it->second.first.x;
				int32_t y = it->second.first.y;
				double distance = std::sqrt( (pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y) );

				// Check if distanceis less or equal to the two radius combined
				if(distance <= it->second.second + radius){
					// if the other circle is bigger
					if(it->second.second > radius){
						return -1;
					// else if the distance is less than or equal
					}else{
						deleteShape(it->first);
						return it->second.second;
					}
				}
			}

			return 0;
		}
	};
	ShapesContainer shapesContainer;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

	void setMainMenu(){
		// Make a text saying to press space bar to start in the center of the screen
		const std::string press = "Press";
		olc::vi2d pressSize = GetTextSize(press);
		const std::string space = "SPACE";
		olc::vi2d spaceSize = GetTextSize(space);
		const std::string to = "to";
		olc::vi2d toSize = GetTextSize(to);
		const std::string start = "start!";
		olc::vi2d startSize = GetTextSize(start);

		DrawString(// Press
			ScreenWidth() / 2 - textScale * (pressSize.x / 2), 
			ScreenHeight() / 2 - textScale * (pressSize.y + spaceSize.y + 2), 
			press, 
			olc::BLACK,
			textScale
		);
		DrawString(// SPACE
			ScreenWidth() / 2 - textScale * (spaceSize.x / 2), 
			ScreenHeight() / 2 - textScale * (spaceSize.y), 
			space, 
			olc::BLACK,
			textScale
		);
		DrawString(// To
			ScreenWidth() / 2 - textScale * (toSize.x / 2), 
			ScreenHeight() / 2 + textScale * (2), 
			to, 
			olc::BLACK,
			textScale
		);
		DrawString(// Start!
			ScreenWidth() / 2 - textScale * (startSize.x / 2), 
			ScreenHeight() / 2 + textScale * (toSize.y + 2), 
			start, 
			olc::BLACK,
			textScale
		);
	}

	void initializeGame(){
		// Set flags
		inMainMenu = true;

		// Initialize the random seed
		srand(time(0));

		// Initialize the struct
		shapesContainer.initialize();

		// Make the background white
		Clear(olc::WHITE);

		drawScore();

		setMainMenu();

		// Set main circle position to middle and its defualt radius
		mainCirclePos = olc::vi2d(ScreenWidth() / 2, ScreenHeight() / 2);
		mainCircleRadius = 10;

		// Set speeds
		otherShapeSpeed = 4;
		MainCircleSpeed = 5;

		// Set LikelyHood
		likelyHood = 50;
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
				mainCirclePos -= olc::vi2d(0, MainCircleSpeed);
			}
		}
		if(downButton.bHeld){
			if(mainCirclePos.y < ScreenHeight()){
				mainCirclePos += olc::vi2d(0, MainCircleSpeed);
			}
		}
		if(leftButton.bHeld){
			if(mainCirclePos.x > 0){
				mainCirclePos -= olc::vi2d(MainCircleSpeed, 0);
			}
		}
		if(rightButton.bHeld){
			if(mainCirclePos.x < ScreenWidth()){
				mainCirclePos += olc::vi2d(MainCircleSpeed, 0);
			}
		}
	}

	// Draw score and level
	void drawScore(){
		// Draw "Score - "
		const std::string scoreTitle = "Score - ";
		olc::vi2d scTitSize = GetTextSize(scoreTitle);
		const std::string levelTitle = "Level - ";
		olc::vi2d lvlTitSize = GetTextSize(levelTitle);

		DrawString(
			0,
			0,
			scoreTitle,
			olc::BLACK,
			textScale
		);
		// Draw the actual score
		DrawString(
			scTitSize.x * textScale,
			0,
			std::to_string(score),
			olc::BLACK,
			textScale
		);

		DrawString(
			0,
			scTitSize.y * textScale,
			levelTitle,
			olc::BLACK,
			textScale
		);
		// Draw actual level
		DrawString(
			lvlTitSize.x * textScale,
			scTitSize.y * textScale,
			std::to_string(level),
			olc::BLACK,
			textScale
		);
	}

	void clearScore(){
		// Make a white rectangle white to clear the score
		const std::string scoreTitle = "Score - ";
		olc::vi2d scTitSize = GetTextSize(scoreTitle);
		olc::vi2d scoreSize = GetTextSize(std::to_string(score));

		int scoreRectLength = textScale * (scTitSize.x + scoreSize.x);
		int scoreRectHeight = textScale * (scTitSize.y + scoreSize.y);

		FillRect(0, 0, scoreRectLength, scoreRectHeight);

		// Make a white rectangle white to clear the level
		const std::string levelTitle = "Level - ";
		olc::vi2d lvlTitSize = GetTextSize(levelTitle);
		olc::vi2d levelSize = GetTextSize(std::to_string(level));

		int levelRectLength = textScale * (lvlTitSize.x + levelSize.x);
		int levelRectHeight = textScale * (lvlTitSize.y + levelSize.y);

		FillRect(0, scoreRectHeight, levelRectLength, levelRectHeight);
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
				score = 0;
				level = 1;
			}
		}else{
			// Clear the Screen where it needs to
			clearScore();
			FillCircle(mainCirclePos, mainCircleRadius, olc::WHITE);
			for(auto it = shapesContainer.begin(); it != shapesContainer.end(); ++it){
				FillCircle(it->second.first, it->second.second, olc::WHITE);
			}

			checkUserInput();

			// Generate shape if needed
			bool maxRateReached = false;
			if(likelyHood - (level - 1) * 5 > 0){
				if(rand() % (likelyHood - (level - 1) * 5) == 0){
					shapesContainer.addShape(ScreenWidth());
				}
			}else{
				if(rand() % 5 == 0){
					shapesContainer.addShape(ScreenWidth());
				}
				maxRateReached = true;
			}

			// Move the shapes down
			shapesContainer.moveShapes(ScreenHeight(), otherShapeSpeed);
			

			// Collision detection
			int collideNumber = shapesContainer.checkCollision2(mainCirclePos, mainCircleRadius);
			if(collideNumber > 0){
				// Make the circle bigger and add to score
				mainCircleRadius += collideNumber / 2;
				score += collideNumber;
			}

			// Check the size for the circle and resize if too big (ie next level)
			if(mainCircleRadius >= 50){
				mainCircleRadius = 10;
				shapesContainer.deleteAllShapes();
				++level;
				if(maxRateReached){
					++otherShapeSpeed;
					++MainCircleSpeed;
				}
			}

			// Draw the screen.
			FillCircle(mainCirclePos, mainCircleRadius, olc::BLUE);
			// Draw the shapes
			for(auto it = shapesContainer.begin(); it != shapesContainer.end(); ++it){
				FillCircle(it->second.first, it->second.second, olc::RED);
			}
			drawScore();

			if(collideNumber == -1){
				// Back to main menu and end the game
				initializeGame();
				inMainMenu = true;
			}
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

#endif