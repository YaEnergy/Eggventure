#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "elements/Button.h"
#include "elements/TextButton.h"
#include "eggCreator.h"
#include "game.h"

#include "assets.h"
#include "Eggventure.h"

Egg Eggs[NUM_EGGS] = {};
Camera2D MainCamera = { {0, 0}, {0, 0}, 0, 1 };
GameState State = Intro;
TextButton startButton = TextButton();

float eggHidingCutsceneTime = 0.0F;

void IntroInit();
void IntroUpdate();
void IntroDraw();

void HidingUpdate();
void HidingDraw();

void GameInit()
{
	for (int i = 0; i < NUM_EGGS; i++)
	{
		Eggs[i].baseColor = WHITE;
		Eggs[i].design = WavyStripes;
		Eggs[i].mark = Star;
		Eggs[i].designColor = LIGHTGRAY;
		Eggs[i].markColor = GRAY;
	}

	IntroInit();
	EggCreatorInit();
}


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
		case EggHiding:
			HidingUpdate();
			HidingDraw();
			break;
		default:
			break;
	}
}

void SetGameState(GameState state)
{
	State = state;
}

void IntroInit()
{
	startButton.TextFont = MainFont;
	startButton.Text = "Play";
	startButton.Background = IconButton_Background;
	startButton.BackgroundNPatchInfo = IconButton_Background_NPatch;
}

void IntroUpdate()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	startButton.FontSize = 48 * ratioMultiplier;
	startButton.Spacing = 4.8F * ratioMultiplier;

	float paddingScreenX = 60 * ratioMultiplier;
	float height = startButton.FontSize + 12 * ratioMultiplier;

	startButton.Rect = { paddingScreenX, screenHeight - height - 15 * ratioMultiplier, screenWidth - paddingScreenX * 2, height };

	startButton.Update(MainCamera);

	if (startButton.Released)
	{
		SetGameState(EggCreation);
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

	startButton.Draw();

	EndDrawing();
}

void HidingUpdate()
{
	eggHidingCutsceneTime += GetFrameTime();

	//Cutscene ends after x seconds
	if (eggHidingCutsceneTime >= 3.0F)
		SetGameState(EggHunt);
}

void HidingDraw()
{
	BeginDrawing();

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	//TODO: add flipping polygon donut sprite
	double time = GetTime();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, SKYBLUE, BLUE, BLUE, SKYBLUE);

	//Title cutscene
	const char* titleText = "Hiding eggs...";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize }, titleFontSize, titleFontSize / 10, WHITE);

	EndDrawing();
}