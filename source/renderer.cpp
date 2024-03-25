#include "raylib.h"
#include "renderer.h"

void DrawTexture(Texture2D texture, Vector2 position, Vector2 origin, float rotationDeg, Vector2 scale, Color tint, bool flipX, bool flipY)
{
	int flipXSign = flipX ? -1 : 1;
	int flipYSign = flipY ? -1 : 1;

	DrawTexturePro(
		texture,
		{ 0, 0, (float)texture.width * flipXSign, (float)texture.height * flipYSign },
		{ position.x,  position.y,  (float)texture.width * scale.x, (float)texture.height * scale.y },
		origin,
		rotationDeg,
		tint
	);
}

Vector2 GetTexturePercentage(Texture2D texture, float x, float y)
{
	return { texture.width * x, texture.height * y };
}