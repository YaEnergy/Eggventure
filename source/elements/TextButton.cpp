#include "raylib.h"
#include "Button.h"
#include "TextButton.h"

void TextButton::MoveTo(Vector2 position)
{
	Rect = { position.x, position.y, Rect.width, Rect.height };
}

void TextButton::FitText()
{
	Vector2 textSize = MeasureTextEx(TextFont, Text, FontSize, Spacing);

	Rect = { Rect.x, Rect.y, textSize.x + Padding * 2, textSize.y + Padding * 2 };
}

void TextButton::Draw()
{
	Color backgroundColor = BackgroundTint;
	Color textColor = TextTint;

	if (Down)
	{
		backgroundColor = ColorTint(BackgroundTint, DownTint);
		textColor = ColorTint(TextTint, DownTint);
	}
	else if (Hovered)
	{
		backgroundColor = ColorTint(BackgroundTint, HoverTint);
		textColor = ColorTint(TextTint, HoverTint);
	}

	DrawTextureNPatch(Background, BackgroundNPatchInfo, Rect, { 0, 0 }, (float)0, backgroundColor);

	Vector2 textSize = MeasureTextEx(TextFont, Text, FontSize, Spacing);

	float textX = 0;

	switch (HorizontalAlignment)
	{
		case Left:
			textX = Padding;
			break;
		case HorizontalCenter:
			textX = (Rect.width - textSize.x) / 2;
			break;
		case Right:
			textX = Rect.width - Padding - textSize.x;
			break;
	}

	float textY = 0;

	switch (VerticalAlignment)
	{
		case Top:
			textY = Padding;
			break;
		case VerticalCenter:
			textY = (Rect.height - textSize.y) / 2;
			break;
		case Bottom:
			textY = Rect.height - Padding - textSize.y;
			break;
	}

	DrawTextEx(TextFont, Text, { Rect.x + textX, Rect.y + textY }, FontSize, Spacing, textColor);
}