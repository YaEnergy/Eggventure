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

float deltaRotatePolygonDonutTime = 0.0f;
float polygonDonutRotateDeg = 20.0f;

float eggHidingCutsceneTime = 0.0f;

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
	deltaRotatePolygonDonutTime = 0.0f;
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

	//rotating polygon donut
	deltaRotatePolygonDonutTime += GetFrameTime();

	if (deltaRotatePolygonDonutTime >= 0.5f)
	{
		deltaRotatePolygonDonutTime = 0.0f;
		polygonDonutRotateDeg = -polygonDonutRotateDeg;
	}
}

void IntroDraw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, RED, PINK, PINK, RED);

	//Title
	const char* titleText = "Polugo n donute's Eggventure!";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize / 2 }, titleFontSize, titleFontSize / 10, WHITE);

#pragma region Introduction text
	float introductionFontSize = 28 * ratioMultiplier;

	float introductionX = 30 * ratioMultiplier;
	float introductionY = (float)screenHeight / 2 - introductionFontSize * 4.5f;

	//TODO: there has to be a better way for doing this... eh too lazy
	const char* introductionText1 = "Polugo n donute has forgor";
	const char* introductionText2 = "to make hideable eggs";
	const char* introductionText3 = "for their event and needs";
	const char* introductionText4 = "your help making every";
	const char* introductionText5 = "single one of them!!!:)";
	const char* introductionText6 = "afterwards he will hide";
	const char* introductionText7 = "them and you'll participate";
	const char* introductionText8 = "in their event!! :3";
	const char* introductionText9 = "(watch out for bunnies!)";

	DrawTextEx(MainFont, introductionText1, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText2, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText3, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText4, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText5, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText6, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText7, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText8, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);

	introductionY += introductionFontSize;

	DrawTextEx(MainFont, introductionText9, { introductionX, introductionY }, introductionFontSize, introductionFontSize / 10, WHITE);


#pragma endregion

	//Start button
	startButton.Draw();

	DrawTexture(PolygonDonutTexture, { screenWidth - PolygonDonutTexture.width / 2.0f - 120 * ratioMultiplier, screenHeight / 2.0f }, { PolygonDonutTexture.width / 2.0f, PolygonDonutTexture.height / 2.0f }, polygonDonutRotateDeg, { 1.0f, 1.0f }, WHITE, false, false);

	EndDrawing();
}

void HidingUpdate()
{
	float deltaTime = GetFrameTime();

	//rotating polygon donut
	deltaRotatePolygonDonutTime += deltaTime;

	if (deltaRotatePolygonDonutTime >= 0.5f)
	{
		deltaRotatePolygonDonutTime = 0.0f;
		polygonDonutRotateDeg = -polygonDonutRotateDeg;
	}

	eggHidingCutsceneTime += deltaTime;

	//Cutscene ends after x seconds
	if (eggHidingCutsceneTime >= 5.0F)
		SetGameState(EggHunt);
}

void HidingDraw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };

	if (eggHidingCutsceneTime < 3.0f)
	{
		DrawRectangleGradientEx(screenRect, SKYBLUE, BLUE, BLUE, SKYBLUE);
	}
	else
	{
		DrawRectangleGradientEx(screenRect, GREEN, DARKGREEN, DARKGREEN, GREEN);
	}

	//Cutscene title
	const char* titleText = eggHidingCutsceneTime < 3.0f ? "Hiding eggs..." : "Go find the eggs!";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize }, titleFontSize, titleFontSize / 10, WHITE);

	//Polygon donut
	DrawTexture(PolygonDonutTexture, { screenWidth / 2.0f, screenHeight / 2.0f + titleFontSize + 10 * ratioMultiplier }, { PolygonDonutTexture.width / 2.0f, PolygonDonutTexture.height / 2.0f }, polygonDonutRotateDeg, { 1.0f, 1.0f }, WHITE, false, false);

	EndDrawing();
}