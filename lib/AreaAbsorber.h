#ifndef AREAABSORBER_H
#define AREAABSORBER_H

#include "GlobalFlags.h"

#include "controllers/InputControls.h"
#include "controllers/ShapeGenerator.h"

#include "containers/ScoreContainer.h"
#include "containers/ShapesContainer.h"

// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class AreaAbsorber : public olc::PixelGameEngine {
	InputControls inputControls;

	// flags
	bool inMainMenu;

	// Text
	const int textScale = 4;
	
	// Shape generator
	ShapeGenerator shapeGenerator;

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
		shapesContainer = ShapesContainer(*this);
		// Initialize the scoreContainer
		scoreContainer = ScoreContainer();
		// Initialize the shape Generator
		shapeGenerator = ShapeGenerator(shapesContainer, scoreContainer);
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

		drawInfoText();

		setMainMenu();

		// Reset the game field
		shapesContainer.reset();
		shapesContainer.resetMainCirclePosition();
		shapesContainer.resetBuddyCircle();
	}

	// Draw score and level
	void drawInfoText(){
		const olc::Pixel textColor = olc::BLACK;
		const std::string infoText = "Score - " + std::to_string(scoreContainer.getScore()) + " " + "Car Life - " + std::to_string(shapesContainer.getMainCircleCarLife()) + '\n'
			+ "Level - " + std::to_string(scoreContainer.getLevel());

		DrawString(
			0,
			0,
			infoText,
			textColor,
			textScale
		);
	}

	void clearInfoText(){
		const std::string infoText = "Score - " + std::to_string(scoreContainer.getScore()) + " " + "Car Life - " + std::to_string(shapesContainer.getMainCircleCarLife()) + '\n'
			+ "Level - " + std::to_string(scoreContainer.getLevel());
		DrawString(
			0,
			0,
			infoText,
			olc::WHITE,
			textScale
		);
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
		if(powerCircleCollideNumber > 0){
			// Make the circle bigger and add to the score
			shapesContainer.growMainCircle(powerCircleCollideNumber / 2);
			scoreContainer.addToScore(powerCircleCollideNumber);
		}

		// Needle Collision detection
		int needleCollideNumber = shapesContainer.checkCollisionForNeedles();
		if(needleCollideNumber == -2){ // Collided with buddy circle
			shapesContainer.subtractLifeToBuddyCircle(3);
		}else if(needleCollideNumber == -4){
			shapesContainer.killMainCircleCar();
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

		// Check for Trap Collision
		int trapCollideNumber = shapesContainer.checkCollisionForTraps();

		// Check Circle Car Collisions
		int circleCarCollidenumber = shapesContainer.checkCollisionForCircleCars();

		return collideNumber == -1 || needleCollideNumber == -1;
	}

	void drawTheScreen(){
		shapesContainer.drawAllShapes();
		drawInfoText();
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
			if(spaceButton.bPressed){
				Clear(olc::WHITE);
				shapesContainer.drawMainCircle();
				inMainMenu = false;
				scoreContainer.resetLevelAndScore();
			}
		}else{
			// Clear the Screen where it needs to
			clearInfoText();
			shapesContainer.hideAll();

			// Shape Generation
			shapeGenerator.runShapeGenerationFrame();

			// Move the shapes
			shapesContainer.moveAllShapes();
			
			// Collision detection
			bool fail = checkCollision();

			// Check the size for the circle and resize if too big (ie next level)
			if(shapesContainer.mainCircleTooBig()){
				// Reset main Circle size for next level
				shapesContainer.clearForNextLevel();
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
