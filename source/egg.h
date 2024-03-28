#pragma once

#include "raylib.h"

const int EGG_DESIGNS_NUM = 5;

enum EggDesign
{
	NoEggDesign = -1,
	SpikyStripes,
	WavyStripes,
	StraightStripes,
	EGG_DESIGN_DOTS
};

const int EGG_MARKS_NUM = 5;

enum EggMark
{
	NoEggMark = -1,
	CatFace,
	Star,
	Circle,
	EGG_MARK_SQUIGGLE
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

Vector2 MeasureEgg(Vector2 scale);