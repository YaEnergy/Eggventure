#pragma once

#include "raylib.h"

//Main
extern Font MainFont;

extern Texture2D SquareTexture;
extern Texture2D PolygonDonutTexture;
extern Texture2D ServerIconTexture;

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

//Marks
extern Texture2D EggMark_CatFace;
extern Texture2D EggMark_Star;
extern Texture2D EggMark_Circle;

void LoadAssets();

void UnloadAssets();