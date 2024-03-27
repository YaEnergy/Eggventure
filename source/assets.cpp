#include "raylib.h"
#include "assets.h"

//Main
Font MainFont = { 0 };
Texture2D PolygonDonutTexture = { 0 };
Texture2D ServerIconTexture = { 0 };

Texture2D IconButton_Background = { 0 };
NPatchInfo IconButton_Background_NPatch = { 0 };

//Discord channels

//Egg
//Egg Base
Texture2D EggBase_Outline = { 0 };
Texture2D EggBase_Color = { 0 };

//Egg Design
Texture2D EggDesign_SpikyStripes = { 0 };
Texture2D EggDesign_WavyStripes = { 0 };
Texture2D EggDesign_StraightStripes = { 0 };

//Egg Marks
Texture2D EggMark_CatFace = { 0 };
Texture2D EggMark_Star = { 0 };
Texture2D EggMark_Circle = { 0 };

void LoadAssets()
{
	//Main
	MainFont = LoadFontEx("assets/Qikki-Reg/Qarmic_sans_Abridged.ttf", 128, NULL, NULL);

	PolygonDonutTexture = LoadTexture("assets/textures/Polygon.png");
	//SetTextureFilter(PolygonDonutTexture, TEXTURE_FILTER_BILINEAR);

	ServerIconTexture = LoadTexture("assets/textures/ServerIcon.png");

	IconButton_Background = LoadTexture("assets/textures/IconButton_Background.png");
	IconButton_Background_NPatch = { { 0, 0, (float)IconButton_Background.width, (float)IconButton_Background.height }, 12, 12, 12, 12, NPATCH_NINE_PATCH };

	//Eggs
	//Base
	EggBase_Outline = LoadTexture("assets/textures/egg/Egg_Shell.png");
	EggBase_Color = LoadTexture("assets/textures/egg/Egg_BaseColor.png");

	//Design
	EggDesign_SpikyStripes = LoadTexture("assets/textures/egg/Egg_SpikeyStripes.png");
	EggDesign_WavyStripes = LoadTexture("assets/textures/egg/Egg_WavyStripes.png");
	EggDesign_StraightStripes = LoadTexture("assets/textures/egg/Egg_StraightStripes.png");

	//Marks
	EggMark_CatFace = LoadTexture("assets/textures/egg/Egg_Mark_CatFace.png");
	EggMark_Star = LoadTexture("assets/textures/egg/Egg_Mark_Star.png");
	EggMark_Circle = LoadTexture("assets/textures/egg/Egg_Mark_Circle.png");
}

void UnloadAssets()
{
	//Main
	UnloadFont(MainFont);

	UnloadTexture(PolygonDonutTexture);
	UnloadTexture(ServerIconTexture);

	UnloadTexture(IconButton_Background);

	//Egg
	//Base
	UnloadTexture(EggBase_Outline);
	UnloadTexture(EggBase_Color);

	//Design
	UnloadTexture(EggDesign_SpikyStripes);
	UnloadTexture(EggDesign_WavyStripes);
	UnloadTexture(EggDesign_StraightStripes);

	//Marks
	UnloadTexture(EggMark_CatFace);
	UnloadTexture(EggMark_Star);
	UnloadTexture(EggMark_Circle);
}