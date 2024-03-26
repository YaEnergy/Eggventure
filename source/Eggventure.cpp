// Eggventure.cpp : Defines the entry point for the application.
//

#include "Eggventure.h"
#include "game.h"
#include "raylib.h"
#include "assets.h"

const char* WINDOW_TITLE = "Polugo n donute's Eggventure!";

const int DESIGN_WIDTH = 800;
const int DESIGN_HEIGHT = 480;

int main()
{
	std::cout << "Polugo n donute's Eggventure! START" << std::endl;

	// Init
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(DESIGN_WIDTH, DESIGN_HEIGHT, WINDOW_TITLE);
	InitAudioDevice();

	SetTargetFPS(120);

	SetWindowState(FLAG_WINDOW_ALWAYS_RUN);

	LoadAssets();

	InitGame();
	
	//TODO: Emscripten for web builds modifications

	//Main loop
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}

	//Deinit
	CloseWindow();
	CloseAudioDevice();

	UnloadAssets();

	return 0;
}

void UpdateDrawFrame()
{
	GameUpdate();
}

float GetScreenDesignRatioMultiplier()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float widthDesignRatio = (float)screenWidth / DESIGN_WIDTH;
	float heightDesignRatio = (float)screenHeight / DESIGN_HEIGHT;

	//Return correct screen design ratio multiplier
	return widthDesignRatio < heightDesignRatio ? widthDesignRatio : heightDesignRatio;
}