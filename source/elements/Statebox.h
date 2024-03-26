#pragma once

#include "raylib.h"
#include "Button.h"

class Statebox : protected Button
{
	public:
		bool State = false;
		bool ChangedThisFrame = false;

		virtual void Update(Camera2D camera);

		Statebox()
		{
			Rect = { NULL, NULL, NULL, NULL };
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