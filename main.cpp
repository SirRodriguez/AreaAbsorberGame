// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

// Ideas
// Circle car that last a certain time and can run over other balls. Has wheels
// Cup that points at you and sucks you in
// Mech suit that will shoot other balls and destroys anything in the way.
// A power up balloon that will raise you up from all the balls
// There is a towel that will go over you or your pet and will block all the needles and other balls. still get score.
// There is a box that traps you for a certain time and the needle can break it open.

// TODO: Fix the color problem in the shapes

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "lib\AreaAbsorber.h"

int main(){
	AreaAbsorber aa;
	const int width = 750;
	const int height = 1000;
	const int pixel_width = 1;
	const int pixel_height = 1;
	const bool full_screen = true;
	const bool vsync = true;
	const bool cohesion = false;
	if(aa.Construct(width, height, pixel_width, pixel_height, full_screen, vsync, cohesion))
		aa.Start();

	return 0;
}