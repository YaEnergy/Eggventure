#include "raylib.h"
#include "assets.h"

//Main
Font MainFont = { 0 };

Image SquareImage = { 0 };
Texture2D SquareTexture = { 0 };
Texture2D PolygonDonutTexture = { 0 };

//Disc stuff
Texture2D ServerIconTexture = { 0 };
Texture2D Channel_GenaralTexture = { 0 };
Texture2D Channel_General2Texture = { 0 };
Texture2D Channel_FishingLakeTexture = { 0 };
Texture2D Channel_StockMarketBoatTexture = { 0 };
Texture2D Channel_TheBusTexture = { 0 };

Texture2D BunnyTexture = { 0 };

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
Texture2D EggDesign_Dots = { 0 };

//Egg Marks
Texture2D EggMark_CatFace = { 0 };
Texture2D EggMark_Star = { 0 };
Texture2D EggMark_Circle = { 0 };
Texture2D EggMark_Squiggle = { 0 };

void LoadAssets()
{
	//Main
	MainFont = LoadFontEx("assets/Qikki-Reg/Qarmic_sans_Abridged.ttf", 128, NULL, NULL);

	SquareImage = GenImageColor(1, 1, WHITE);
	SquareTexture = LoadTextureFromImage(SquareImage);

	PolygonDonutTexture = LoadTexture("assets/textures/Polygon.png");
	SetTextureFilter(PolygonDonutTexture, TEXTURE_FILTER_BILINEAR);

	ServerIconTexture = LoadTexture("assets/textures/ServerIcon.png");
	SetTextureFilter(ServerIconTexture, TEXTURE_FILTER_BILINEAR);

	Channel_GenaralTexture = LoadTexture("assets/textures/channels/genaral.png");
	SetTextureFilter(Channel_GenaralTexture, TEXTURE_FILTER_BILINEAR);

	Channel_General2Texture = LoadTexture("assets/textures/channels/general2.png");
	SetTextureFilter(Channel_General2Texture, TEXTURE_FILTER_BILINEAR);

	Channel_FishingLakeTexture = LoadTexture("assets/textures/channels/fishinglake.png");
	SetTextureFilter(Channel_FishingLakeTexture, TEXTURE_FILTER_BILINEAR);

	Channel_StockMarketBoatTexture = LoadTexture("assets/textures/channels/stockmarketboat.png");
	SetTextureFilter(Channel_StockMarketBoatTexture, TEXTURE_FILTER_BILINEAR);

	Channel_TheBusTexture = LoadTexture("assets/textures/channels/thebus.png");
	SetTextureFilter(Channel_TheBusTexture, TEXTURE_FILTER_BILINEAR);

	BunnyTexture = LoadTexture("assets/textures/Bunny.png");
	SetTextureFilter(BunnyTexture, TEXTURE_FILTER_BILINEAR);

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
	EggDesign_Dots = LoadTexture("assets/textures/egg/Egg_Dots.png");

	//Marks
	EggMark_CatFace = LoadTexture("assets/textures/egg/Egg_Mark_CatFace.png");
	EggMark_Star = LoadTexture("assets/textures/egg/Egg_Mark_Star.png");
	EggMark_Circle = LoadTexture("assets/textures/egg/Egg_Mark_Circle.png");
	EggMark_Squiggle = LoadTexture("assets/textures/egg/Egg_Mark_Squiggle.png");
}

void UnloadAssets()
{
	//Main
	UnloadFont(MainFont);

	UnloadImage(SquareImage);
	UnloadTexture(SquareTexture);
	UnloadTexture(PolygonDonutTexture);
	UnloadTexture(ServerIconTexture);

	UnloadTexture(Channel_GenaralTexture);
	UnloadTexture(Channel_General2Texture);
	UnloadTexture(Channel_FishingLakeTexture);
	UnloadTexture(Channel_StockMarketBoatTexture);
	UnloadTexture(Channel_TheBusTexture);

	UnloadTexture(BunnyTexture);

	UnloadTexture(IconButton_Background);

	//Egg
	//Base
	UnloadTexture(EggBase_Outline);
	UnloadTexture(EggBase_Color);

	//Design
	UnloadTexture(EggDesign_SpikyStripes);
	UnloadTexture(EggDesign_WavyStripes);
	UnloadTexture(EggDesign_StraightStripes);
	UnloadTexture(EggDesign_Dots);

	//Marks
	UnloadTexture(EggMark_CatFace);
	UnloadTexture(EggMark_Star);
	UnloadTexture(EggMark_Circle);
	UnloadTexture(EggMark_Squiggle);
}