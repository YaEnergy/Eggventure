#pragma once

//Main
extern Font MainFont;
//extern Font DiscordChannelFont;

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