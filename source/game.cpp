#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "elements/Button.h"
#include "elements/TextButton.h"
#include "eggCreator.h"
#include "eggHunt.h"
#include "game.h"
#include "elements/FadeScreen.h"

#include "assets.h"
#include "Eggventure.h"

Egg Eggs[NUM_EGGS] = {};
Camera2D MainCamera = { {0, 0}, {0, 0}, 0, 1 };
GameState State = Intro;
TextButton startButton = TextButton();

bool hasStarted = false;

float deltaRotatePolygonDonutTime = 0.0f;
float polygonDonutRotateDeg = 20.0f;

float eggHidingCutsceneTime = 0.0f;
bool eggsHidden = false;
bool hasHidingCutsceneEnded = false;

void IntroInit();
void IntroUpdate();
void IntroDraw();

void HidingUpdate();
void HidingDraw();

void WinUpdate();
void WinDraw();

void GameInit()
{
	for (int i = 0; i < NUM_EGGS; i++)
	{
		Eggs[i].baseColor = WHITE;
		Eggs[i].design = NoEggDesign;
		Eggs[i].mark = NoEggMark;
		Eggs[i].designColor = LIGHTGRAY;
		Eggs[i].markColor = GRAY;
	}

	IntroInit();
	EggCreatorInit();
	EggHuntInit();
}


void GameUpdate()
{
	float deltaTime = GetFrameTime();
	UpdateFadeScreen(deltaTime);

	BeginDrawing();

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
		case EggHunt:
			EggHuntUpdate();
			EggHuntDraw();
			break;
		case Win:
			WinUpdate();
			WinDraw();
			break;
		default:
			break;
	}

	DrawFadeScreen();

	EndDrawing();
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

	startButton.UpdateButton(MainCamera);

	if (startButton.Released && !hasStarted)
	{
		PlaySound(SFX_Start);
		
		FadeScreenIn(1.0f, BLACK);
		hasStarted = true;
	}

	//rotating polygon donut
	deltaRotatePolygonDonutTime += GetFrameTime();

	if (deltaRotatePolygonDonutTime >= 0.5f)
	{
		deltaRotatePolygonDonutTime = 0.0f;
		polygonDonutRotateDeg = -polygonDonutRotateDeg;
	}

	//Music
	if (!IsMusicStreamPlaying(Music_Main))
	{
		PlayMusicStream(Music_Main);
	}

	UpdateMusicStream(Music_Main);

	if (hasStarted && HasFadeFinished())
	{
		SetGameState(EggCreation);
		FadeScreenOut(1.0f, BLACK);
	}
}

void IntroDraw()
{
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

	//TODO: there has to be a better way for doing this... eh too lazy to change it now though
	//could've just set the line spacing, because I didn't know that function existed, if I ever need to make a change here I'll use that instead
	//but prob won't need to anymore
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
	
	//Play cool sfx after 3 seconds
	if (eggHidingCutsceneTime >= 3.0f && !eggsHidden)
	{
		eggsHidden = true;
		PlaySound(SFX_EggCollect);
	}

	//Cutscene ends after 5 seconds
	if (eggHidingCutsceneTime >= 5.0F)
	{
		if (!hasHidingCutsceneEnded)
		{
			hasHidingCutsceneEnded = true;
			FadeScreenIn(1.0f, BLACK);
		}
		else if (hasHidingCutsceneEnded && HasFadeFinished())
		{
			SetGameState(EggHunt);
			FadeScreenOut(1.0f, BLACK);
		}
	}

	//Music
	if (!IsMusicStreamPlaying(Music_Main))
	{
		PlayMusicStream(Music_Main);
	}

	UpdateMusicStream(Music_Main);
}

void HidingDraw()
{
	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };

	if (eggsHidden)
	{
		DrawRectangleGradientEx(screenRect, GREEN, DARKGREEN, DARKGREEN, GREEN);
	}
	else
	{
		DrawRectangleGradientEx(screenRect, SKYBLUE, BLUE, BLUE, SKYBLUE);
	}

	//Cutscene title
	const char* titleText = eggsHidden ? "Go find the eggs!" : "Hiding eggs...";
	float titleFontSize = 56 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize }, titleFontSize, titleFontSize / 10, WHITE);

	//Polygon donut
	DrawTexture(PolygonDonutTexture, { screenWidth / 2.0f, screenHeight / 2.0f + titleFontSize + 10 * ratioMultiplier }, { PolygonDonutTexture.width / 2.0f, PolygonDonutTexture.height / 2.0f }, polygonDonutRotateDeg, { 1.0f, 1.0f }, WHITE, false, false);
}

void WinUpdate()
{
	float deltaTime = GetFrameTime();

	//rotating polygon donut
	deltaRotatePolygonDonutTime += deltaTime;

	if (deltaRotatePolygonDonutTime >= 0.5f)
	{
		deltaRotatePolygonDonutTime = 0.0f;
		polygonDonutRotateDeg = -polygonDonutRotateDeg;
	}

	if (!IsMusicStreamPlaying(Music_Main))
	{
		PlayMusicStream(Music_Main);
	}

	UpdateMusicStream(Music_Main);
}

void WinDraw()
{
	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };

	DrawRectangleGradientEx(screenRect, GREEN, DARKGREEN, DARKGREEN, GREEN);

	//Polygon donut
	DrawTexture(PolygonDonutTexture, { screenWidth / 2.0f, screenHeight / 2.0f + 66 * ratioMultiplier }, { PolygonDonutTexture.width / 2.0f, PolygonDonutTexture.height / 2.0f }, polygonDonutRotateDeg, { 1.0f, 1.0f }, WHITE, false, false);

	//Cutscene title
	const char* titleText1 = "You found all the eggs!";
	const char* titleText2 = "Thanks for playing!";
	float titleFontSize = 56 * ratioMultiplier;

	SetTextLineSpacing((int)(titleFontSize + 15 * ratioMultiplier));

	Vector2 titleSize1 = MeasureTextEx(MainFont, titleText1, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText1, { (screenWidth - titleSize1.x) / 2, titleFontSize }, titleFontSize, titleFontSize / 10, WHITE);

	Vector2 titleSize2 = MeasureTextEx(MainFont, titleText2, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText2, { (screenWidth - titleSize2.x) / 2, titleFontSize * 2 + 5 * ratioMultiplier }, titleFontSize, titleFontSize / 10, WHITE);

	///"Burn The World Waltz", "Pleasant Porridge"
	///Kevin MacLeod(incompetech.com)
	///Licensed under Creative Commons : By Attribution 3.0
	///http://creativecommons.org/licenses/by/3.0/ 

	const char* creditsText = "\"Burn The World Waltz\", \"Pleasant Porridge\"\nKevin MacLeod(incompetech.com)\nLicensed under Creative Commons : By Attribution 3.0\nhttp://creativecommons.org/licenses/by/3.0/";
	float creditsFontSize = 24 * ratioMultiplier;

	SetTextLineSpacing((int)(creditsFontSize + 5 * ratioMultiplier));

	DrawTextEx(MainFont, creditsText, { 10 * ratioMultiplier, screenHeight - creditsFontSize * 4 - 30 * ratioMultiplier }, creditsFontSize, creditsFontSize / 10, WHITE);
}