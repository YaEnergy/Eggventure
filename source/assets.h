#pragma once

//Main
extern Font MainFont;
//extern Font DiscordChannelFont;

extern Texture2D IconButton_Background;
extern NPatchInfo IconButton_Background_NPatch;

//Discord channel backgrounds

//Eggs
//Egg Base
extern Texture2D EggBase_Outline;
extern Texture2D EggBase_Color;

//Egg Designs
extern Texture2D EggDesign_SpikyStripes_Color;
extern Texture2D EggDesign_WavyStripes_Color;
extern Texture2D EggDesign_StraightStripes_Color;

extern Texture2D EggDesign_SpikyStripes_Outline;
extern Texture2D EggDesign_WavyStripes_Outline;
extern Texture2D EggDesign_StraightStripes_Outline;

//Marks
extern Texture2D EggMark_CatFace;
extern Texture2D EggMark_Star;
extern Texture2D EggMark_Circle;

void LoadAssets();

void UnloadAssets();