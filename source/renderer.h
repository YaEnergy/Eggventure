#pragma once

#include "raylib.h"

void DrawTexture(Texture2D texture, Vector2 position, Vector2 origin, float rotationDeg, Vector2 scale, Color tint, bool flipX, bool flipY);

Vector2 GetTexturePercentage(Texture2D texture, float x, float y);