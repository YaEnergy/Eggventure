#pragma once

#include "raylib.h"

const int EGG_DESIGNS_NUM = 4;

enum EggDesign
{
	NoEggDesign,
	SpikyStripes,
	WavyStripes,
	StraightStripes
};

const int EGG_MARKS_NUM = 4;

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

Vector2 MeasureEgg(Vector2 scale);