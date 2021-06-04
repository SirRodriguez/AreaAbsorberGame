#ifndef AREAABSORBER_H
#define AREAABSORBER_H

#include "GlobalFlags.h"

#include "controllers\InputControls.h"
#include "controllers\ShapeGenerator.h"
#include "controllers\ShapeMover.h"

#include "containers\ScoreContainer.h"
#include "containers\ShapesContainer.h"

// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class AreaAbsorber : public olc::PixelGameEngine {
	InputControls inputControls;

	// flags
	bool inMainMenu;

	// Text
	const int textScale = 4;
	// Mover
	ShapeMover shapeMover;
	ShapeGenerator shapeGenerator;
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
	ScoreContainer scoreContainer;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

	void constructObjects(){
		// Initialize the input controls class
		inputControls = InputControls(*this);
		// Initialize the hape container
		shapesContainer.initialize(*this);
		// Initialize the scoreContainer
		scoreContainer = ScoreContainer();
		// Initialize the shape Generator
		shapeGenerator = ShapeGenerator(shapesContainer, scoreContainer);
		// Initialize the shape mover
		shapeMover = ShapeMover(shapesContainer);
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

		// Make the background white
		Clear(olc::WHITE);

		drawScore();

		setMainMenu();

		// Set speeds
		shapeMover.setOtherCircleSpeed(4);
		shapeMover.setPowerUpSpeed(2);
		shapeMover.setPowerUpCircleSpeed(5);
		shapeMover.setNeedleSpeed(6);
		shapeMover.setBuddyPowerUpSpeed(2);
		shapeMover.setBuddyCircleSpeed(2);
		shapeMover.setMainCircleSpeed(5);

		// Set LikelyHood
		shapeGenerator.setLikelyHoodOfCircles(50);
		shapeGenerator.setLikelyHoodOfPowerUps(500);
		shapeGenerator.setLikelyHoodOfNeedles(1000);
		shapeGenerator.setLikelyHoodOfBuddyPowerUps(1000);
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
			std::to_string(scoreContainer.getScore()),
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
			std::to_string(scoreContainer.getLevel()),
			olc::BLACK,
			textScale
		);
	}

	void clearScore(){
		// Make a white rectangle white to clear the score
		const std::string scoreTitle = "Score - ";
		olc::vi2d scTitSize = GetTextSize(scoreTitle);
		olc::vi2d scoreSize = GetTextSize(std::to_string(scoreContainer.getScore()));

		int scoreRectLength = textScale * (scTitSize.x + scoreSize.x);
		int scoreRectHeight = textScale * (scTitSize.y + scoreSize.y);

		FillRect(0, 0, scoreRectLength, scoreRectHeight);

		// Make a white rectangle white to clear the level
		const std::string levelTitle = "Level - ";
		olc::vi2d lvlTitSize = GetTextSize(levelTitle);
		olc::vi2d levelSize = GetTextSize(std::to_string(scoreContainer.getLevel()));

		int levelRectLength = textScale * (lvlTitSize.x + levelSize.x);
		int levelRectHeight = textScale * (lvlTitSize.y + levelSize.y);

		FillRect(0, scoreRectHeight, levelRectLength, levelRectHeight);
	}

	bool checkCollision(){
		// Collision detection
		int collideNumber = shapesContainer.checkCollisionForCircle();
		if(collideNumber > 0){
			// Make the circle bigger and add to score
			shapesContainer.growMainCircle(collideNumber / 2);
			scoreContainer.addToScore(collideNumber);
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
			scoreContainer.addToScore(powerCircleCollideNumber);
		}

		// Needle Collision detection
		int needleCollideNumber = shapesContainer.checkCollisionForNeedles();
		if(needleCollideNumber == -2){ // Collided with buddy circle
			shapesContainer.subtractLifeToBuddyCircle(3);
		}

		// Buddy Power Up collision
		int buddyPowerUpCollideNumber = shapesContainer.checkCollisionForBuddyPowerUps();
		if(buddyPowerUpCollideNumber == -1){
			shapesContainer.addLifeToBuddyCircle(5);
		}

		// Buddy Circle Collision
		int buddyCircleCollideNumber = shapesContainer.checkCollisionForBuddyCircle();
		if(buddyCircleCollideNumber > 0){
			shapesContainer.growMainCircle(buddyCircleCollideNumber / 2);
			scoreContainer.addToScore(buddyCircleCollideNumber);
			shapesContainer.subtractLifeToBuddyCircle(1);
		}else if(buddyCircleCollideNumber < 0){
			shapesContainer.subtractLifeToBuddyCircle(3);
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
		constructObjects();
		initializeGame();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// Update input controls
		inputControls.runInputFrame();

		// Called Once per frame
		if(inMainMenu){
			// spaceButton = GetKey(olc::Key::SPACE);
			if(spaceButton.bPressed){
				Clear(olc::WHITE);
				shapesContainer.drawMainCircle(mainCircleColor);
				inMainMenu = false;
				scoreContainer.resetLevelAndScore();
			}
		}else{
			// Clear the Screen where it needs to
			clearScore();
			shapesContainer.hideAll();

			// Shape Generation
			shapeGenerator.runShapeGenerationFrame();

			// Move the shapes
			shapeMover.runMoveShapesFrame();
			
			// Collision detection
			bool fail = checkCollision();

			// Check the size for the circle and resize if too big (ie next level)
			if(shapesContainer.mainCircleTooBig()){
				// Reset main Circle size for next level
				shapesContainer.reset();
				scoreContainer.incrementLevel();
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