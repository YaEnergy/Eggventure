#include "game.h"
#include "raylib.h"
#include "assets.h"
#include "Eggventure.h"

GameState State = Intro;

void GameUpdate()
{
	switch (State)
	{
		case Intro:
			IntroDraw();
			break;
		default:
			break;
	}
}

void IntroDraw()
{
	BeginDrawing();

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	double time = GetTime();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, screenWidth, screenHeight };
	DrawRectangleGradientEx(screenRect, RED, PINK, PINK, RED);

	//Title
	const char* titleText = "Polugo n donute's Eggventure!";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize / 2 }, titleFontSize, titleFontSize / 10, WHITE);

	//Introduction text
	float introductionFontSize = 28 * ratioMultiplier;

	float introductionY = (float)screenHeight / 2 - introductionFontSize * 4;

	//TODO: there has to be a better way for doing this...
	const char* introductionText1 = "Polugo n donute has forgor";
	const char* introductionText2 = "to make hideable eggs";
	const char* introductionText3 = "your help making every";
	const char* introductionText4 = "single one of them!!!:)";
	const char* introductionText5 = "afterwards he will hide";
	const char* introductionText6 = "them and you'll participate";
	const char* introductionText7 = "in their event!! :3";
	const char* introductionText8 = "(watch out for bunnies!)";

	DrawTextEx(MainFont, introductionText1, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText2, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText3, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText4, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText5, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText6, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText7, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText8, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	//Start text
	const char* startText = "Click to start!";
	float startFontSize = 48 * ratioMultiplier;
	Vector2 startSize = MeasureTextEx(MainFont, startText, startFontSize, startFontSize / 10);
	DrawTextEx(MainFont, startText, { (screenWidth - startSize.x) / 2, screenHeight - startFontSize * (float)1.5 }, startFontSize, startFontSize / 10, WHITE);

	EndDrawing();
}