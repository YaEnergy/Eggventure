#pragma once

#include "raylib.h"

enum EggDesign
{
	NoEggDesign,
	SpikyStripes,
	WavyStripes,
	StraightStripes
};

enum EggMark
{
	NoEggMark,
	CatFace,
	Star,
	Circle
};

struct Egg
{
	Color baseColor;
	EggDesign design;
	Color designColor;
	EggMark mark;
	Color markColor;
};

void DrawEgg(Egg egg, Vector2 position, Vector2 origin, float rotationDeg, Vector2 scale, Color tint);