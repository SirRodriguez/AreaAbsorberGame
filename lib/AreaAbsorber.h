#ifndef AREAABSORBER
#define AREAABSORBER

#include "shapes\ShapesContainer.h"
#include "shapes\derivedShapes\Circle.h"

// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

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
	int MainShapeSpeed;
	// Score
	int score;
	int level;
	// Likelyhood of other circles generated
	int likelyHood;
	// Colors
	const olc::Pixel mainCircleColor = olc::BLACK;
	const olc::Pixel otherCircleColor = olc::RED;
	const olc::Pixel powerUpColor = olc::GREEN;


	// Other shapes containers
	ShapesContainer shapesContainer;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";

		score = 0;
		level = 0;
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
		shapesContainer.initialize(*this);

		// Make the background white
		Clear(olc::WHITE);

		drawScore();

		setMainMenu();

		// Set speeds
		otherShapeSpeed = 4;
		MainShapeSpeed = 5;

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
			shapesContainer.moveMainCircleUp(MainShapeSpeed);
		}
		if(downButton.bHeld){
			shapesContainer.moveMainCircleDown(MainShapeSpeed);
		}
		if(leftButton.bHeld){
			shapesContainer.moveMainCircleLeft(MainShapeSpeed);
		}
		if(rightButton.bHeld){
			shapesContainer.moveMainCircleRight(MainShapeSpeed);
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
				shapesContainer.drawMainCircle(mainCircleColor);
				inMainMenu = false;
				score = 0;
				level = 1;
			}
		}else{
			// Clear the Screen where it needs to
			clearScore();
			shapesContainer.hideAll();

			// User input
			checkUserInput();

			// Generate shape if needed
			bool maxRateReached = false;
			if(likelyHood - (level - 1) * 5 > 0){
				if(rand() % (likelyHood - (level - 1) * 5) == 0){
					shapesContainer.addCircle();
				}
			}else{
				if(rand() % 5 == 0){
					shapesContainer.addCircle();
				}
				maxRateReached = true;
			}

			// Move the shapes down
			shapesContainer.moveShapes(otherShapeSpeed);
			
			// Collision detection
			int collideNumber = shapesContainer.checkCollisionForCircle();
			if(collideNumber > 0){
				// Make the circle bigger and add to score
				shapesContainer.growMainCircle(collideNumber / 2);
				score += collideNumber;
			}

			// Check the size for the circle and resize if too big (ie next level)
			if(shapesContainer.mainCircleTooBig()){
				shapesContainer.setMainCircleRadius(10);
				shapesContainer.deleteAllCircles();
				++level;
				if(maxRateReached){
					++otherShapeSpeed;
					++MainShapeSpeed;
				}
			}

			// Draw the screen.
			shapesContainer.drawMainCircle(mainCircleColor);
			// Draw the shapes
			shapesContainer.drawCircles(otherCircleColor);
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