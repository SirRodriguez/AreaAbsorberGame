// Command to compile 
// g++ -o main.exe main.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "AreaAbsorber.h"

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