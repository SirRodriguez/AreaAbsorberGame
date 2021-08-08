#include "../GlobalFlags.h"

class InputControls{
	olc::PixelGameEngine* pixelGameEngine;

	void updateButtons(){
		// Get the up, down, left, right buttons
		upButton = pixelGameEngine->GetKey(olc::Key::UP);
		downButton = pixelGameEngine->GetKey(olc::Key::DOWN);
		leftButton = pixelGameEngine->GetKey(olc::Key::LEFT);
		rightButton = pixelGameEngine->GetKey(olc::Key::RIGHT);

		// Check the space button
		spaceButton = pixelGameEngine->GetKey(olc::Key::SPACE);

		// Check the escape button
		escButton = pixelGameEngine->GetKey(olc::Key::ESCAPE);

		// Check the shift button
		shiftButton = pixelGameEngine->GetKey(olc::Key::SHIFT);
	}

public:
	// Constructors
	InputControls()
	: pixelGameEngine(nullptr){}
	InputControls(olc::PixelGameEngine& pge)
	: pixelGameEngine(&pge){}

	// Check the inputs and executes the inputs
	void runInputFrame(){
		updateButtons();
	}
};