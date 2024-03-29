#ifndef AREAABSORBER_H
#define AREAABSORBER_H

#include "GlobalConstants.h"
#include "GlobalFlags.h"

#include "controllers/InputControls.h"
#include "controllers/ShapeGenerator.h"

#include "containers/ScoreContainer.h"
#include "containers/ShapesContainer.h"
#include "containers/AnimationContainer.h"

// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

class AreaAbsorber : public olc::PixelGameEngine {
	InputControls* inputControls = nullptr;

	// flags
	bool inMainMenu;

	// Text
	const int textScale = 4;
	
	// Shape generator
	ShapeGenerator* shapeGenerator = nullptr;

	// Containers
	ShapesContainer shapesContainer;
	ScoreContainer scoreContainer;
	AnimationContainer animationContainer;

public:
	AreaAbsorber(){
		sAppName = "AreaAbsorber";
	}

	void constructObjects(){
		// Initialize the input controls class
		inputControls = new InputControls(*this);
		// Initialize Animation Container
		animationContainer = AnimationContainer();
		animationContainer.initializePopStorage(*this);
		// Initialize the hape container
		shapesContainer = ShapesContainer(*this, animationContainer);
		// Initialize the scoreContainer
		scoreContainer = ScoreContainer(*this, animationContainer);
		// Initialize the shape Generator
		shapeGenerator = new ShapeGenerator(shapesContainer, scoreContainer);
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
		const olc::vf2d position = olc::vf2d(0,0);
		const olc::Pixel textColor = olc::BLACK;
		const std::string infoText = "Score - " + std::to_string(scoreContainer.getScore()) + " " + "Car Life - " + std::to_string(shapesContainer.getMainCircleCarLife()) + '\n'
			+ "Level - " + std::to_string(scoreContainer.getLevel());
		const olc::vf2d scale = olc::vf2d(1.0f, 1.0f) * textScale;

		DrawStringDecal(
			position,
			infoText,
			textColor,
			scale
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

		// Check Nukes Collision
		int nukesCollideNumber = shapesContainer.checkCollisionForNukes();
		if(nukesCollideNumber == -1){
			shapesContainer.runNuke();
		}

		// Check collision with boss circle
		int bossCollideNumber = shapesContainer.checkCollisionForBossCircle();

		return collideNumber == -1 || needleCollideNumber == -1 || bossCollideNumber > 0;
	}

	void drawTheScreen(){
		animationContainer.drawAnimationsFrame();
		shapesContainer.drawAllShapes();
		drawInfoText();
	}

public:
	bool OnUserCreate() override {
		// Load the sprites
		whiteCircleSprite = new olc::Sprite(whiteCircleFile);
		whiteEquilateralTriangleSprite = new olc::Sprite(whiteEquilateralTriangleFile);
		whiteLineSprite = new olc::Sprite(whiteLineFile);
		whiteSquareOutlineSprite = new olc::Sprite(whiteSquareOutlineFile);

		// Called once at the start, so create things here
		constructObjects();
		initializeGame();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// Update input controls
		inputControls->runInputFrame();

		// Called Once per frame
		if(inMainMenu){
			drawInfoText();
			if(spaceButton.bPressed){
				Clear(olc::WHITE);
				inMainMenu = false;
				scoreContainer.resetLevelAndScore();
			}
		}else{
			// Shape Generation
			shapeGenerator->runShapeGenerationFrame();

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

	bool OnUserDestroy() override {
		delete whiteCircleSprite;
		delete whiteEquilateralTriangleSprite;
		delete whiteLineSprite;
		delete whiteSquareOutlineSprite;

		return true;
	}
};

#endif
