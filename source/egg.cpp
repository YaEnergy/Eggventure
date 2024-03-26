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
			DrawTexture(EggDesign_SpikyStripes_Color, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			DrawTexture(EggDesign_SpikyStripes_Outline, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
		case WavyStripes:
			DrawTexture(EggDesign_WavyStripes_Color, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			DrawTexture(EggDesign_WavyStripes_Outline, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			break;
		case StraightStripes:
			DrawTexture(EggDesign_StraightStripes_Color, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
			DrawTexture(EggDesign_StraightStripes_Outline, position, origin, rotationDeg, scale, ColorTint(egg.designColor, tint), false, false);
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
	}

	DrawTexture(EggBase_Outline, position, origin, rotationDeg, scale, ColorTint(egg.baseColor, tint), false, false);
}