#pragma once

#include "raylib.h"

//why am i using extern, eh whatever

//Main
extern Font MainFont;

extern Texture2D SquareTexture;
extern Texture2D PolygonDonutTexture;

//Disc stuff
extern Texture2D ServerIconTexture;
extern Texture2D Channel_GenaralTexture;
extern Texture2D Channel_General2Texture;
extern Texture2D Channel_FishingLakeTexture;
extern Texture2D Channel_StockMarketBoatTexture;
extern Texture2D Channel_TheBusTexture;

extern Texture2D BunnyTexture;

extern Texture2D IconButton_Background;
extern NPatchInfo IconButton_Background_NPatch;

//Discord channel backgrounds

//Eggs
//Egg Base
extern Texture2D EggBase_Outline;
extern Texture2D EggBase_Color;

//Egg Designs
extern Texture2D EggDesign_SpikyStripes;
extern Texture2D EggDesign_WavyStripes;
extern Texture2D EggDesign_StraightStripes;
extern Texture2D EggDesign_Dots;
extern Texture2D EggDesign_Squiggles;

//Marks
extern Texture2D EggMark_CatFace;
extern Texture2D EggMark_Star;
extern Texture2D EggMark_Circle;
extern Texture2D EggMark_Squiggle;
extern Texture2D EggMark_Heart;

//SFX
extern Sound SFX_Start;
extern Sound SFX_EggCollect;
extern Sound SFX_EggEditorSelect;
extern Sound SFX_ClickBunny;
extern Sound SFX_Win;

//Music
extern Music Music_Main;
extern Music Music_Bunny;

void LoadAssets();

void UnloadAssets();