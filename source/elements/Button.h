#pragma once

#include "raylib.h"

bool IsRectHovered(Rectangle rect, Camera2D camera);

class Button
{
	public:
		Rectangle Rect;
		
		bool Hovered = false;
		bool Pressed = false;
		bool Released = false;
		bool Down = false;

		void Update(Camera2D camera);

		bool IsHovered(Camera2D camera) const;
		bool IsReleased(Camera2D camera) const;
		bool IsPressed(Camera2D camera) const;
		bool IsDown(Camera2D camera) const;
		bool IsUp(Camera2D camera) const;

		Button()
		{
			Rect = { 0 };
		}

		Button(Rectangle rect)
		{
			Rect = rect;
		}

		~Button()
		{

		}
};