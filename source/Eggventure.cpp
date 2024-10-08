﻿// Eggventure.cpp : Defines the entry point for the application.
//

#include "Eggventure.h"
#include "game.h"
#include "raylib.h"
#include "assets.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif


const char* WINDOW_TITLE = "Polugo n donute's Eggventure!";

const int DESIGN_WIDTH = 800;
const int DESIGN_HEIGHT = 480;

float gamePassedTime = 0.0f;

#ifdef WIN32RELEASE

//I love dumb work arounds! (me no like console window on windows...)
int WinMain()
{
	return main();
}
#endif // RELEASE


int main()
{
	std::cout << "Polugo n donute's Eggventure! START" << std::endl;

	// Init
	InitWindow(DESIGN_WIDTH, DESIGN_HEIGHT, WINDOW_TITLE);
	InitAudioDevice();
	
	SetWindowMinSize(DESIGN_WIDTH / 2, DESIGN_HEIGHT / 2);
	SetWindowState(FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE);

	//Set working directory to application directory
	ChangeDirectory(GetApplicationDirectory());

	Image icon = LoadImage("assets/Icon.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); //Required for icons

	SetWindowIcon(icon);

	UnloadImage(icon);

	LoadAssets();

	GameInit();
	
	//TODO: Emscripten for web builds modifications

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(120);
	//Main loop
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
#endif

	//Deinit


	UnloadAssets();

	CloseAudioDevice();

	CloseWindow();

	return 0;
}

void UpdateDrawFrame()
{
	gamePassedTime += GetFrameTime();

	SetMasterVolume(gamePassedTime <= 4.0f ? gamePassedTime / 4.0f : 1.0f);

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