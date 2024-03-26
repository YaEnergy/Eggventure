#pragma once

#include "raylib.h"
#include "Button.h"
#include "UIUtils.h"

class TextButton : public Button
{
	public:
		Texture Background;
		Color BackgroundTint = WHITE;
		NPatchInfo BackgroundNPatchInfo;

		Font TextFont;
		const char* Text;
		float FontSize;
		float Spacing;
		Color TextTint = BLACK;

		HorizontalAlignment TextHorizontalAlignment = HorizontalCenter;
		VerticalAlignment TextVerticalAlignment = VerticalCenter;

		float Padding = 0;

		Color HoverTint = LIGHTGRAY;
		Color DownTint = GRAY;

		void MoveTo(Vector2 position);
		void FitText();
		void Draw();

		TextButton()
		{
			Background = { 0 };
			BackgroundNPatchInfo = { 0 };

			TextFont = GetFontDefault();
			Text = "";
			FontSize = 12;
			Spacing = 1.2F;
		}

		TextButton(Rectangle rect, Texture background, NPatchInfo backgroundNPatchInfo, Font font, const char* text, float fontSize, float spacing) : Button(rect)
		{
			Background = background;
			BackgroundNPatchInfo = backgroundNPatchInfo;
			TextFont = font;
			Text = text;
			FontSize = fontSize;
			Spacing = spacing;
		}
};