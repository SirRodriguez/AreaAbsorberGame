// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

// Ideas
// Cup that points at you and sucks you in
// Mech suit that will shoot other balls and destroys anything in the way.
// A power up balloon that will raise you up from all the balls
// There is a towel that will go over you or your pet and will block all the needles and other balls. still get score.
// Power up that freezes other balls
// A Boss Level
// A nuke
// Star that makes you invincible
// Wave that you can ride that will absorbe other circles
// slime that you turn into the size of the slime and absorbs other circle, then you turn into the size of the slime.

// TODO
// Put the buddy circle as part of the main circle class
// Put the collide functions in the shape classes.


#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "lib/AreaAbsorber.h"

int main(){
	AreaAbsorber aa;
	const int width = 1000;
	const int height = 1000;
	const int pixel_width = 1;
	const int pixel_height = 1;

	const bool full_screen = true;
	const bool vsync = true; // Game made to run at 60 fps
	const bool cohesion = false;
	if(aa.Construct(width, height, pixel_width, pixel_height, full_screen, vsync, cohesion))
		aa.Start();

	return 0;
}