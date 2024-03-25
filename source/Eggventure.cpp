// Eggventure.cpp : Defines the entry point for the application.
//

#include "Eggventure.h"
#include "raylib.h"

const char* WINDOW_TITLE = "Polugo n donute's Eggventure!";

const int DESIGN_WIDTH = 800;
const int DESIGN_HEIGHT = 480;

Texture2D test;

int main()
{
	std::cout << "Polugo n donute's Eggventure!" << std::endl;

	// Init
	InitWindow(DESIGN_WIDTH, DESIGN_HEIGHT, WINDOW_TITLE);
	InitAudioDevice();

	test = LoadTexture("assets/egg/Egg_SpikeyStripes.png");

	//TODO: Emscripten for web builds modifications

	//Main loop
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}

	UnloadTexture(test);

	//Deinit
	CloseWindow();
	CloseAudioDevice();

	return 0;
}

static void UpdateDrawFrame()
{
	BeginDrawing();

	ClearBackground(WHITE);

	DrawText("This is a text", 0, 0, 36, BLACK);

	DrawTexture(test, 0, 0, WHITE);

	EndDrawing();
}