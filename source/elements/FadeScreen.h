#pragma once

void UpdateFadeScreen(float deltaTime);

void DrawFadeScreen();

void FadeScreenIn(float timeSeconds, Color color);

void FadeScreenOut(float timeSeconds, Color color);

bool IsScreenFading();

bool HasFadeFinished();

bool IsFadingIn();

bool IsFadingOut();