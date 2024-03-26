#pragma once

#include "raylib.h"
#include "egg.h"
#include "elements/UIUtils.h"
#include "elements/Statebox.h"

class EggStatebox : public Statebox
{
	public:
		Texture Background;
		Color BackgroundTint = WHITE;
		NPatchInfo BackgroundNPatchInfo;

		Egg BoxEgg;
		Vector2 EggScale = { 1, 1 };
		Color EggTint = WHITE;

		HorizontalAlignment EggHorizontalAlignment = HorizontalCenter;
		VerticalAlignment EggVerticalAlignment = VerticalCenter;

		float Padding = 0;

		Color DefaultTrueTint = GREEN;

		Color HoverFalseTint = LIGHTGRAY;
		Color DownFalseTint = GRAY;
		Color HoverTrueTint = { 0, 160, 48, 255 }; //If only 3 green colors existed...
		Color DownTrueTint = DARKGREEN;

		void MoveTo(Vector2 position);
		void Draw();

		EggStatebox()
		{
			BoxEgg = { 0 };
			Background = { 0 };
			BackgroundNPatchInfo = { 0 };
		}

		EggStatebox(Rectangle rect, bool state, Egg egg, Texture2D background, NPatchInfo backgroundNPatchInfo) : Statebox(rect, state)
		{
			BoxEgg = egg;
			Background = background;
			BackgroundNPatchInfo = backgroundNPatchInfo;
		}
};
