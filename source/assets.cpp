#include "raylib.h"
#include "assets.h"

//Main
Font MainFont = { 0 };
//Font DiscordChannelFont = { 0 };

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
	MainFont = LoadFont("assets/Qikki-Reg/Qarmic_sans_Abridged.ttf");

	//Eggs
	//Base
	EggBase_Outline = LoadTexture("assets/egg/Egg_Shell.png");
	EggBase_Color = LoadTexture("assets/egg/Egg_BaseColor.png");

	//Design
	EggDesign_SpikyStripes = LoadTexture("assets/egg/Egg_SpikeyStripes.png");
	EggDesign_WavyStripes = LoadTexture("assets/egg/Egg_WavyStripes.png");
	EggDesign_StraightStripes = LoadTexture("assets/egg/Egg_Stripes.png");

	//Marks
	EggMark_CatFace = LoadTexture("assets/egg/Egg_Mark_CatFace.png");
	EggMark_Star = LoadTexture("assets/egg/Egg_Mark_Star.png");
	EggMark_Circle = LoadTexture("assets/egg/Egg_Mark_Circle.png");
}

void UnloadAssets()
{
	//Main
	UnloadFont(MainFont);

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