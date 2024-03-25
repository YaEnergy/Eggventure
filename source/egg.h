#pragma once

enum EggDesign
{
	None,
	SpikyStripes,
	WavyStripes,
	StraightStripes
};

enum EggMark
{
	None,
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

void DrawEgg(Egg egg, Vector2 position, float rotation, float scale);