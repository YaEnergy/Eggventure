#include <iostream>
#include "raylib.h"
#include "Button.h"

bool IsRectHovered(Rectangle rect, Camera2D camera)
{
	Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

	return mouseWorldPos.x >= rect.x && mouseWorldPos.x <= rect.x + rect.width && mouseWorldPos.y >= rect.y && mouseWorldPos.y <= rect.y + rect.height;
}

void Button::Update(Camera2D camera)
{
	Hovered = IsHovered(camera);
	Pressed = Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	Released = Hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
	Down = Hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

bool Button::IsHovered(Camera2D camera) const
{
	return IsRectHovered(Rect, camera);
}

bool Button::IsPressed(Camera2D camera) const
{
	return IsHovered(camera) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool Button::IsReleased(Camera2D camera) const
{
	return IsHovered(camera) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

bool Button::IsDown(Camera2D camera) const
{
	return IsHovered(camera) && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

bool Button::IsUp(Camera2D camera) const
{
	bool hovered = IsHovered(camera);
	bool mouseButtonUp = IsMouseButtonUp(MOUSE_BUTTON_LEFT);

	return (hovered && mouseButtonUp) || !hovered;
}
