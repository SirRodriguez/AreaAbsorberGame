// Command to compile 
// g++ -o AreaAbsorber.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

// Ideas
// Mech suit that will shoot other balls and destroys anything in the way.
// A power up balloon that will raise you up from all the balls
// There is a towel that will go over you or your pet and will block all the needles and other balls. still get score.
// Power up that freezes other balls
// Star that makes you invincible
// Wave that you can ride that will absorbe other circles
// slime that you turn into the size of the slime and absorbs other circle, then you turn into the size of the slime.
// Fire
// Power up to get a flame thrower

// Bug Find out why the destructor does not work in Circle class
// Also why contruction of objects is too slow
// In MainCircleList, Remove the mainCircle as a pointer and make it normal
// Move direction to shape base class

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "lib/AreaAbsorber.h"

int main(){
	AreaAbsorber aa;
	const int width = 1500;
	const int height = 1500;
	const int pixel_width = 1;
	const int pixel_height = 1;

	const bool full_screen = true;
	const bool vsync = true; // Game made to run at 60 fps
	const bool cohesion = false;
	if(aa.Construct(width, height, pixel_width, pixel_height, full_screen, vsync, cohesion))
		aa.Start();

	return 0;
}