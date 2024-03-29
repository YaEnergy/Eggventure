// Eggventure.cpp : Defines the entry point for the application.
//

#include "Eggventure.h"
#include "game.h"
#include "raylib.h"
#include "assets.h"

//#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
	//#include <emscripten/emscripten.h>
#endif


const char* WINDOW_TITLE = "Polugo n donute's Eggventure!";

const int DESIGN_WIDTH = 800;
const int DESIGN_HEIGHT = 480;

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


	SetWindowState(FLAG_WINDOW_ALWAYS_RUN);

	Image icon = LoadImage("assets/Icon.png");

	SetWindowIcon(icon);


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

	//Deinit
	CloseWindow();
#endif

	CloseAudioDevice();

	UnloadImage(icon);

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