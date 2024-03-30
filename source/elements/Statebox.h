#pragma once

#include "raylib.h"
#include "Button.h"

class Statebox : public Button
{
	public:
		bool State = false;

		void UpdateStatebox(Camera2D camera);

		Statebox()
		{
			Rect = { 0, 0, 1, 1 };
			State = false;
		}

		Statebox(Rectangle rect)
		{
			Rect = rect;
			State = false;
		}

		Statebox(Rectangle rect, bool state)
		{
			Rect = rect;
			State = state;
		}
};