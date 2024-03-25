#pragma once

bool IsRectHovered(Rectangle rect, Camera2D camera);

class Button
{
	public:
		Rectangle Rect;

		bool IsHovered(Camera2D camera) const;
		bool IsReleased(Camera2D camera) const;
		bool IsPressed(Camera2D camera) const;
		bool IsDown(Camera2D camera) const;
		bool IsUp(Camera2D camera) const;

		Button(Rectangle rect)
		{
			Rect = rect;
		}
};