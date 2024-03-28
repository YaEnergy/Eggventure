#include "raylib.h"
#include "egg.h"
#include "renderer.h"
#include "assets.h"

void DrawEgg(Egg egg, Vector2 position, Vector2 origin, float rotationDeg, Vector2 scale, Color tint)
{
	DrawTexture(EggBase_Color, position, origin, rotationDeg, scale, ColorTint(egg.baseColor, tint), false, false);

	switch (egg.design)
	{
		case SpikyStripes:
			DrawTexture(EggDesign_SpikyStripes, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
		case WavyStripes:
			DrawTexture(EggDesign_WavyStripes, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
		case StraightStripes:
			DrawTexture(EggDesign_StraightStripes, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
		case EGG_DESIGN_DOTS:
			DrawTexture(EggDesign_Dots, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
	}

	switch (egg.mark)
	{
		case CatFace:
			DrawTexture(EggMark_CatFace, position, origin, rotationDeg, scale, ColorTint(egg.markColor, tint), false, false);
			break;
		case Star:
			DrawTexture(EggMark_Star, position, origin, rotationDeg, scale, ColorTint(egg.markColor, tint), false, false);
			break;
		case Circle:
			DrawTexture(EggMark_Circle, position, origin, rotationDeg, scale, ColorTint(egg.markColor, tint), false, false);
			break;
		case EGG_MARK_SQUIGGLE:
			DrawTexture(EggMark_Squiggle, position, origin, rotationDeg, scale, ColorTint(egg.markColor, tint), false, false);
			break;
	}

	DrawTexture(EggBase_Outline, position, origin, rotationDeg, scale, ColorTint(egg.baseColor, tint), false, false);
}

Vector2 MeasureEgg(Vector2 scale)
{
	return { EggBase_Outline.width * scale.x, EggBase_Outline.height * scale.y };
}