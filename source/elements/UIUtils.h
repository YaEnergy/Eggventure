#pragma once

#include "raylib.h"

enum HorizontalAlignment
{
	Left,
	Right,
	HorizontalCenter
};

enum VerticalAlignment
{
	Top,
	VerticalCenter,
	Bottom
};

bool IsRectHovered(Rectangle rect, Camera2D camera);