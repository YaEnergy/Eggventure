#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "game.h"
#include "eggCreator.h"

#include "assets.h"
#include "Eggventure.h"

GameState State = Intro;

void IntroUpdate();
void IntroDraw();

void GameUpdate()
{
	switch (State)
	{
		case Intro:
			IntroUpdate();
			IntroDraw();
			break;
		case EggCreation:
			EggCreatorUpdate();
			EggCreatorDraw();
			break;
		default:
			break;
	}
}

void IntroUpdate()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		State = EggCreation;
	}
}

void IntroDraw()
{
	BeginDrawing();

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	//TODO: add flipping polygon donut sprite
	double time = GetTime();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, RED, PINK, PINK, RED);

	//Title
	const char* titleText = "Polugo n donute's Eggventure!";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize / 2 }, titleFontSize, titleFontSize / 10, WHITE);

	//Introduction text
	float introductionFontSize = 28 * ratioMultiplier;

	float introductionY = (float)screenHeight / 2 - introductionFontSize * 4.5F;

	//TODO: there has to be a better way for doing this...
	const char* introductionText1 = "Polugo n donute has forgor";
	const char* introductionText2 = "to make hideable eggs";
	const char* introductionText3 = "for their event and needs";
	const char* introductionText4 = "your help making every";
	const char* introductionText5 = "single one of them!!!:)";
	const char* introductionText6 = "afterwards he will hide";
	const char* introductionText7 = "them and you'll participate";
	const char* introductionText8 = "in their event!! :3";
	const char* introductionText9 = "(watch out for bunnies!)";

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

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText9, { 10 * ratioMultiplier, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	//Start text
	const char* startText = "Click to start!";
	float startFontSize = 48 * ratioMultiplier;
	Vector2 startSize = MeasureTextEx(MainFont, startText, startFontSize, startFontSize / 10);
	DrawTextEx(MainFont, startText, { (screenWidth - startSize.x) / 2, screenHeight - startFontSize * (float)1.5 }, startFontSize, startFontSize / 10, WHITE);

	EndDrawing();
}