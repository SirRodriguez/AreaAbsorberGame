#ifndef AREAABSORBER
#define AREAABSORBER

#include "shapes\ShapesContainer.h"
#include "shapes\derivedShapes\Circle.h"
#include "shapes\derivedShapes\Triangle.h"

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
	int otherCircleSpeed;
	int powerUpSpeed;
	int powerUpCircleSpeed;
	int needleSpeed;
	int buddyPowerUpSpeed;
	int buddyCircleSpeed;
	int MainCircleSpeed;
	// Score
	int score;
	int level;
	// Likelyhood of other circles generated
	int likelyHoodOfCircles;
	int likelyHoodOfPowerUps;
	int likelyHoodOfNeedles;
	int likelyHoodOfBuddyPowerUps;
	// Colors
	const olc::Pixel mainCircleColor = olc::BLACK;
	const olc::Pixel otherCircleColor = olc::RED;
	const olc::Pixel powerUpColor = olc::GREEN;
	const olc::Pixel powerUpCircleColors = olc::GREY;
	const olc::Pixel needleColor = olc::BLACK;
	const olc::Pixel buddyPowerUpColor = olc::YELLOW;
	const olc::Pixel buddyCircleColor = olc::DARK_GREY;


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
		otherCircleSpeed = 4;
		powerUpSpeed = 2;
		powerUpCircleSpeed = 5;
		needleSpeed = 6;
		buddyPowerUpSpeed = 2;
		buddyCircleSpeed = 2;
		MainCircleSpeed = 5;

		// Set LikelyHood
		likelyHoodOfCircles = 50;
		likelyHoodOfPowerUps = 1000;
		likelyHoodOfNeedles = 1000;
		likelyHoodOfBuddyPowerUps = 1000;
	}

	void checkUserInput(){
		// Get the up, down, left, right buttons
		upButton = GetKey(olc::Key::UP);
		downButton = GetKey(olc::Key::DOWN);
		leftButton = GetKey(olc::Key::LEFT);
		rightButton = GetKey(olc::Key::RIGHT);

		// Update the position of the circle
		if(upButton.bHeld){
			shapesContainer.moveMainCircleUp(MainCircleSpeed);
		}
		if(downButton.bHeld){
			shapesContainer.moveMainCircleDown(MainCircleSpeed);
		}
		if(leftButton.bHeld){
			shapesContainer.moveMainCircleLeft(MainCircleSpeed);
		}
		if(rightButton.bHeld){
			shapesContainer.moveMainCircleRight(MainCircleSpeed);
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

	void shapeGeneration(){
		// Generate Circle if needed
		if(likelyHoodOfCircles - (level - 1) * 5 > 0){
			if(rand() % (likelyHoodOfCircles - (level - 1) * 5) == 0){
				shapesContainer.addCircle();
			}
		}else{
			// This is the max rate of circle generation
			if(rand() % 5 == 0){
				shapesContainer.addCircle();
			}
		}

		// Generate Powerup if needed
		if(likelyHoodOfPowerUps - (level - 1) * 50 > 0){
			if(rand() % (likelyHoodOfPowerUps - (level - 1) * 50) == 0){
				shapesContainer.addPowerUp();
			}
		}else{
			if(rand() % 50 == 0){
				shapesContainer.addPowerUp();
			}
		}

		// Generate Needles if needed
		if(likelyHoodOfNeedles - (level - 1) * 100 > 0){
			if(rand() % (likelyHoodOfNeedles - (level - 1) * 100) == 0){
				shapesContainer.addNeedle();
			}
		}else{
			if(rand() % 50 == 0){
				shapesContainer.addNeedle();
			}
		}

		// Generate budd power ups
		if(likelyHoodOfBuddyPowerUps - (level - 1) * 100 > 0){
			if(rand() % (likelyHoodOfBuddyPowerUps - (level - 1) * 100) == 0){
				shapesContainer.addBuddyPowerUp();
			}
		}else{
			if(rand() % 50 == 0){
				shapesContainer.addBuddyPowerUp();
			}
		}
	}

	void moveShapesDown(){
		shapesContainer.moveCircles(otherCircleSpeed);
		shapesContainer.movePowerUps(powerUpSpeed);
		shapesContainer.movePowerUpCircles(powerUpCircleSpeed);
		shapesContainer.moveNeedles(needleSpeed);
		shapesContainer.moveBuddyPowerUps(buddyPowerUpSpeed);
		shapesContainer.moveBuddyCircle(buddyCircleSpeed);
	}

	bool checkCollision(){
		// Collision detection
		int collideNumber = shapesContainer.checkCollisionForCircle();
		if(collideNumber > 0){
			// Make the circle bigger and add to score
			shapesContainer.growMainCircle(collideNumber / 2);
			score += collideNumber;
		}

		// Power up collision detection
		int powerCollideNumber = shapesContainer.checkCollisionForPowerUps();
		if(powerCollideNumber == 1){
			// Make power up
			shapesContainer.addPowerUpCircles();
		}

		// Power up circle collision detection for other circles
		int powerCircleCollideNumber = shapesContainer.checkCollisionForPowerUpCircles();
		if(powerCircleCollideNumber == 0){
			// Make the circle bigger and add to the score
			shapesContainer.growMainCircle(powerCircleCollideNumber / 2);
			score += powerCircleCollideNumber;
		}

		// Needle Collision detection
		int needleCollideNumber = shapesContainer.checkCollisionForNeedles();

		// Buddy Power Up collision
		int buddyPowerUpCollideNumber = shapesContainer.checkCollisionForBuddyPowerUps();
		if(buddyPowerUpCollideNumber == -1){
			shapesContainer.addLifeToBuddyCircle(5);
		}

		// Buddy Circle Collision
		int buddyCircleCollideNumber = shapesContainer.checkCollisionForBuddyCircle();
		if(buddyCircleCollideNumber > 0){
			shapesContainer.growMainCircle(buddyCircleCollideNumber / 2);
			score += buddyCircleCollideNumber;
			shapesContainer.subtractLifeToBuddyCircle(1);
		}else if(buddyCircleCollideNumber < 0){
			shapesContainer.subtractLifeToBuddyCircle(2);
		}

		return collideNumber == -1 || needleCollideNumber == -1;
	}

	void drawTheScreen(){
		shapesContainer.drawMainCircle(mainCircleColor);
		// Draw the shapes
		shapesContainer.drawCircles(otherCircleColor);
		shapesContainer.drawPowerUps(powerUpColor);
		shapesContainer.drawPowerUpCircles(powerUpCircleColors);
		shapesContainer.drawNeedles(needleColor);
		shapesContainer.drawBuddyPowerUps(buddyPowerUpColor);
		shapesContainer.drawBuddyCircle(buddyCircleColor);
		drawScore();
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

			// Shape Generation
			shapeGeneration();

			// Move the shapes down
			moveShapesDown();
			
			// Collision detection
			bool fail = checkCollision();

			// Check the size for the circle and resize if too big (ie next level)
			if(shapesContainer.mainCircleTooBig()){
				// Reset main Circle size for next level
				shapesContainer.reset();
				++level;
			}

			// Draw the screen.
			drawTheScreen();

			if(fail){
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