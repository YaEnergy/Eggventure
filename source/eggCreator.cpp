#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "elements/TextButton.h"
#include "eggCreator.h"
#include "game.h"
#include "assets.h"
#include "Eggventure.h"

int EggIndex = 0;

void EggCreatorUpdate()
{

}

void EggCreatorDraw()
{
	BeginDrawing();

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, ORANGE, RED, RED, ORANGE);

	float eggEditorHeight = 150 * ratioMultiplier;

	int eggWidth = EggBase_Outline.width;
	int eggHeight = EggBase_Outline.height;
	
	DrawEgg(Eggs[EggIndex], { (float)screenWidth / 2, (float)(screenHeight - eggEditorHeight) / 2 }, { (float)eggWidth / 2, (float)eggHeight / 2 }, 0, { 1, 1 }, WHITE);

	DrawRectangleRec({ 0, screenHeight - eggEditorHeight, (float)screenWidth, eggEditorHeight}, RAYWHITE);

	EndDrawing();
}