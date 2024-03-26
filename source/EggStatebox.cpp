#include "raylib.h"
#include "elements/UIUtils.h"
#include "EggStatebox.h"

void EggStatebox::MoveTo(Vector2 position)
{
	Rect = { position.x, position.y, Rect.width, Rect.height };
}

void EggStatebox::Draw()
{
	Color backgroundColor = ColorTint(BackgroundTint, State ? DefaultTrueTint : WHITE);

	//Is EggStateBox Down?
	if (Down)
	{
		backgroundColor = ColorTint(BackgroundTint, State ? DownTrueTint : DownFalseTint);
	}
	//Is EggStateBox only hovered?
	else if (Hovered)
	{
		backgroundColor = ColorTint(BackgroundTint, State ? HoverTrueTint : HoverFalseTint);
	}

	DrawTextureNPatch(Background, BackgroundNPatchInfo, Rect, { 0, 0 }, (float)0, backgroundColor);

	Vector2 eggSize = MeasureEgg(EggScale);

	float eggPosX = 0;

	switch (EggHorizontalAlignment)
	{
		case Left:
			eggPosX = Padding;
			break;
		case HorizontalCenter:
			eggPosX = (Rect.width - eggSize.x) / 2;
			break;
		case Right:
			eggPosX = Rect.width - eggSize.x - Padding;
			break;
	}

	float eggPosY = 0;

	switch (EggVerticalAlignment)
	{
		case Top:
			eggPosY = Padding;
			break;
		case VerticalCenter:
			eggPosY = (Rect.height - eggSize.y) / 2;
			break;
		case Bottom:
			eggPosY = Rect.height - eggSize.y - Padding;
			break;
	}

	DrawEgg(BoxEgg, { Rect.x + eggPosX, Rect.y + eggPosY }, { 0, 0 }, 0, EggScale, EggTint);
}
