#include "raylib.h"
#include "FadeScreen.h"

Color fadeColor = BLACK;
float screenAlpha = 0.0f;

bool isTransitioning = false;

bool fadingIn = false;

float transitionTime = 0.0f;
float passedTime = 0.0f;

void UpdateFadeScreen(float deltaTime)
{
	if (passedTime < transitionTime)
	{
		passedTime += deltaTime;
		screenAlpha = fadingIn ? passedTime / transitionTime : 1.0f - (passedTime / transitionTime);
	}
	else
	{
		passedTime = transitionTime;
		screenAlpha = fadingIn ? 1.0f : 0.0f;
	}
}

void DrawFadeScreen()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(fadeColor, screenAlpha));
}

void FadeScreenIn(float timeSeconds, Color color)
{
	transitionTime = timeSeconds;
	passedTime = 0.0f;
	fadeColor = color;

	fadingIn = true;
}

void FadeScreenOut(float timeSeconds, Color color)
{
	transitionTime = timeSeconds;
	passedTime = 0.0f;
	fadeColor = color;

	fadingIn = false;
}

bool IsScreenFading()
{
	return passedTime < transitionTime && transitionTime != 0.0f;
}

bool HasFadeFinished()
{
	return passedTime >= transitionTime && transitionTime != 0.0f;
}