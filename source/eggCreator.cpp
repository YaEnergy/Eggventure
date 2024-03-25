#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "eggCreator.h"

int EggIndex = 0;

void EggCreatorUpdate()
{

}

void EggCreatorDraw()
{
	BeginDrawing();

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, ORANGE, RED, RED, ORANGE);

	EndDrawing();
}