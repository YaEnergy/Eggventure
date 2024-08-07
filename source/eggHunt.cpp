﻿#include "eggHunt.h"
#include "assets.h"
#include "renderer.h"
#include "egg.h"
#include "game.h"
#include "Eggventure.h"
#include "elements/TextButton.h"
#include "elements/UIUtils.h"
#include "elements/FadeScreen.h"
#include "raymath.h"

#include <cmath>

const float BASE_FONT_SIZE = 16.0f;

const int NUM_CHANNELS = 5;

//this is some awful code, wow
//now it's even worse!

enum DiscordChannel
{
	DISCORD_CHANNEL_GENARAL, //Best channel name
	DISCORD_CHANNEL_GENERAL_2,
	DISCORD_CHANNEL_FISHING_LAKE,
	DISCORD_CHANNEL_STOCK_MARKET_BOAT,
	DISCORD_CHANNEL_THE_BUS,
};

Vector2 backgroundStartPosition = Vector2{ 0.0f, 0.0f };
float backgroundScale = 1.0f;

int numFoundEggs = 0;
Vector2 eggScale = { 0.25f, 0.25f };
Vector2 eggPosition = { 0, 0 };
DiscordChannel eggChannel = DISCORD_CHANNEL_GENARAL;

Vector2 bunnyPosition = { 0, 0 };
Vector2 bunnyScale = { 0.5f, 0.5f };
Vector2 bunnyVelocity = { 0, 0 };
float bunnySpeed = 75.0f;

int bunnyClicksLeft = 5;
float deltaBunnyClickTime = 0.0f;

bool hasEggHuntEnded = false;

DiscordChannel currentChannel = DISCORD_CHANNEL_GENARAL;

TextButton channelButtons[NUM_CHANNELS] = { TextButton(), TextButton(), TextButton(), TextButton(), TextButton() };

bool IsEggHovered();
bool IsBunnyHovered();
void ChangeChannel(DiscordChannel channel);
void RandomHideEgg();
const char* GetChannelName(DiscordChannel channel);
const char* GetChannelNameTag(DiscordChannel channel);
Texture2D& GetChannelBackgroundTexture(DiscordChannel channel);

void EggHuntInit()
{
	//mmm i love copying values over, allowing me to make changes and forgetting to make them somewhere else
	float barHeight = 50.0f;
	float serverListWidth = 75.0f;
	float channelListWidth = 225.0f;

	float channelTextSize = BASE_FONT_SIZE / MeasureTextEx(MainFont, "AAAAAAAAAAAAAAAA", BASE_FONT_SIZE, BASE_FONT_SIZE / 10).x * (channelListWidth - 25);

	// Button set up!!!
	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		channelButtons[i].FontSize = channelTextSize;
		channelButtons[i].TextFont = MainFont;
		channelButtons[i].Text = GetChannelNameTag((DiscordChannel)i); //add hashtag infront of here
		channelButtons[i].Background = SquareTexture;
		channelButtons[i].BackgroundNPatchInfo = { 0, 0, 0, 0, NPATCH_NINE_PATCH };
		channelButtons[i].BackgroundTint = BLANK;
		channelButtons[i].HoverTint = LIGHTGRAY;
		channelButtons[i].TextTint = WHITE;
		channelButtons[i].Padding = 15;
		channelButtons[i].TextHorizontalAlignment = Left;

		channelButtons[i].Rect = { serverListWidth, barHeight + 15 + (channelTextSize + 10) * i, channelListWidth, channelTextSize + 10};
	}

	//da bunny
	deltaBunnyClickTime = 0.5f;

	float bunnyAngleDeg = (float)GetRandomValue(0, 360);
	bunnyVelocity = { cosf(bunnyAngleDeg) * bunnySpeed, sinf(bunnyAngleDeg) * bunnySpeed };

	//do some randomisation crap here or something idk
	numFoundEggs = 0;
	RandomHideEgg();

	//finish
	ChangeChannel(DISCORD_CHANNEL_GENARAL);
}

void EggHuntUpdate()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//mmm i love copying values over, allowing me to make changes and forgetting to make them somewhere else
	//v1.0.1 edit: why did i do this, whatever

	float barHeight = 50.0f;
	float serverListWidth = 75.0f;
	float channelListWidth = 225.0f;

	//Update channel buttons
	//and channel
	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		channelButtons[i].UpdateButton(MainCamera);

		if (channelButtons[i].Released)
		{
			ChangeChannel((DiscordChannel)i);
		}
	}

	Texture2D& backgroundTexture = GetChannelBackgroundTexture(currentChannel);
	float channelWidth = screenWidth - serverListWidth - channelListWidth;
	float channelHeight = screenHeight - barHeight;

	float channelPaddingX = (channelWidth - (float)backgroundTexture.width * backgroundScale) / 2.0f;
	float channelPaddingY = (channelHeight - (float)backgroundTexture.height * backgroundScale) / 2.0f;

	backgroundScale = std::min(channelWidth / (float)backgroundTexture.width, channelHeight / (float)backgroundTexture.height);
	backgroundStartPosition = Vector2{ serverListWidth + channelListWidth + channelPaddingX, barHeight + channelPaddingY };

	Vector2 eggSize = MeasureEgg(eggScale);

	// bunny egg movement
	if (numFoundEggs >= NUM_EGGS - 1 && currentChannel == eggChannel)
	{
		float deltaTime = GetFrameTime();

		deltaBunnyClickTime += deltaTime;

		bunnyPosition = { bunnyPosition.x + bunnyVelocity.x * deltaTime, bunnyPosition.y + bunnyVelocity.y * deltaTime };

		//collision stuff here
		Texture2D& backgroundTexture = GetChannelBackgroundTexture(eggChannel);

		bool isCollidingX = false;
		float collisionX = 0;

		if (bunnyPosition.x > (float)backgroundTexture.width - BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionX = (float)backgroundTexture.width - BunnyTexture.width * bunnyScale.x / 2.0f;
			isCollidingX = true;
		}
		else if (bunnyPosition.x < BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionX = BunnyTexture.width * bunnyScale.x / 2.0f;
			isCollidingX = true;
		}

		if (isCollidingX)
		{
			float deltaX = bunnyPosition.x - collisionX;

			//adjust bunny back
			bunnyPosition.x = collisionX;
			bunnyPosition.y -= (bunnyVelocity.y / bunnyVelocity.x) * deltaX;

			bunnyVelocity = { -bunnyVelocity.x, bunnyVelocity.y };
		}

		bool isCollidingY = false;
		float collisionY = 0;

		if (bunnyPosition.y > (float)backgroundTexture.height - BunnyTexture.height * bunnyScale.y / 2.0f)
		{
			collisionY = (float)backgroundTexture.height - BunnyTexture.height * bunnyScale.y / 2.0f;
			isCollidingY = true;
		}
		else if (bunnyPosition.y < BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionY = BunnyTexture.width * bunnyScale.x / 2.0f;
			isCollidingY = true;
		}

		if (isCollidingY)
		{
			float deltaY = bunnyPosition.y - collisionY;

			//adjust bunny back
			bunnyPosition.x -= (bunnyVelocity.x / bunnyVelocity.y) * deltaY;
			bunnyPosition.y = collisionY;

			bunnyVelocity = { bunnyVelocity.x, -bunnyVelocity.y };
		}

		//egg should follow bunny if it is still holding it
		if (bunnyClicksLeft > 0)
		{
			eggPosition = { bunnyPosition.x, bunnyPosition.y - BunnyTexture.height * bunnyScale.y / 2.0f };
		}
	}

	//Check if egg is clicked and found, (or bunny if they exist)
	if ((IsEggHovered() || (IsBunnyHovered() && numFoundEggs == NUM_EGGS - 1 && bunnyClicksLeft > 0)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentChannel == eggChannel && numFoundEggs < NUM_EGGS)
	{
		if (numFoundEggs == NUM_EGGS - 1 && bunnyClicksLeft > 0)
		{
			PlaySound(SFX_ClickBunny);
			bunnyClicksLeft--;

			//Double bunny speed
			bunnySpeed *= 2;
			bunnyVelocity = { bunnyVelocity.x * 2, bunnyVelocity.y * 2 };

			deltaBunnyClickTime = 0.0f;
		}
		else
		{
			numFoundEggs++;
			PlaySound(SFX_EggCollect);

			if (numFoundEggs != NUM_EGGS)
				RandomHideEgg();
		}
	}

	//La music
	if (bunnyClicksLeft == 0 || numFoundEggs != NUM_EGGS - 1 || currentChannel != eggChannel)
	{
		if (!IsMusicStreamPlaying(Music_Main))
		{
			PlayMusicStream(Music_Main);
		}

		UpdateMusicStream(Music_Main);
	}
	else
	{
		if (!IsMusicStreamPlaying(Music_Bunny))
		{
			PlayMusicStream(Music_Bunny);
		}

		UpdateMusicStream(Music_Bunny);
	}

	//If all eggs have been found, fade to win scene
	if (numFoundEggs == NUM_EGGS && !hasEggHuntEnded)
	{
		PlaySound(SFX_Win);

		hasEggHuntEnded = true;

		FadeScreenIn(1.0f, BLACK);
	}
	else if (hasEggHuntEnded && HasFadeFinished())
	{
		SetGameState(Win);
		FadeScreenOut(1.0f, BLACK);
	}
}

bool IsEggHovered()
{
	//egg and bunny also scaled by the background scale

	Vector2 trueEggPos = Vector2Add(Vector2Scale(eggPosition, backgroundScale), backgroundStartPosition);
	Vector2 eggSize = MeasureEgg(Vector2Scale(eggScale, backgroundScale));
	return IsRectHovered({ trueEggPos.x - eggSize.x / 2, trueEggPos.y - eggSize.y / 2,  eggSize.x, eggSize.y }, MainCamera);
}

bool IsBunnyHovered()
{
	//egg and bunny also scaled by the background scale

	Vector2 truePos = Vector2Add(Vector2Scale(bunnyPosition, backgroundScale), backgroundStartPosition);
	Vector2 trueScale = Vector2Scale(bunnyScale, backgroundScale);
	return IsRectHovered({ truePos.x - BunnyTexture.width * trueScale.x / 2, truePos.y - BunnyTexture.height * trueScale.y / 2, BunnyTexture.width * trueScale.x, BunnyTexture.height * trueScale.y }, MainCamera);
}

void ChangeChannel(DiscordChannel channel)
{
	Color selectedColor = { 255, 255, 255, 100 };
	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		channelButtons[i].BackgroundTint = i == channel ? selectedColor : BLANK;
	}

	currentChannel = channel;
}

void RandomHideEgg()
{
	float screenHeight = GetScreenHeight();
	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Random channel, just not the current egg channel

	DiscordChannel oldChannel = eggChannel;

	while (oldChannel == eggChannel)
	{
		eggChannel = (DiscordChannel)GetRandomValue(0, NUM_CHANNELS - 1);
	}

	Vector2 eggSize = MeasureEgg(eggScale);
	Vector2 benchEggSize = MeasureEgg({ 0.35f * ratioMultiplier, 0.35f * ratioMultiplier });

	Texture2D& backgroundTexture = GetChannelBackgroundTexture(eggChannel);

	Vector2 newEggPosition = { (float)GetRandomValue((int)(eggSize.x / 2.0f), (int)((float)backgroundTexture.width - eggSize.x / 2.0f)), (float)GetRandomValue((int)(eggSize.y / 2.0f), (int)((float)backgroundTexture.height - eggSize.y / 2.0f)) };//{ (float)GetRandomValue((int)(eggSize.x / 2.0f), (int)((float)backgroundTexture.width - eggSize.x / 2.0f)), (float)GetRandomValue((int)(eggSize.y / 2.0f), (int)((float)backgroundTexture.height - eggSize.y / 2.0f)) };
	
	//if new egg position (in the channel background space) is under the y-level of the found eggs bench, move the new egg position to just above the found eggs bench
	//kind of a dirty solution, but it works
	if (Vector2Add(Vector2Scale(newEggPosition, backgroundScale), backgroundStartPosition).y > (float)screenHeight - benchEggSize.y - MeasureEgg(Vector2Scale(eggScale, backgroundScale)).y / 2.0f)
		newEggPosition.y = ((float)screenHeight - benchEggSize.y - MeasureEgg(Vector2Scale(eggScale, backgroundScale)).y / 2.0f - backgroundStartPosition.y) / backgroundScale;

	eggPosition = newEggPosition;
	bunnyPosition = eggPosition;
}

void EggHuntDraw()
{
	ClearBackground(WHITE);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Server list
	float serverListWidth = 75.0f;
	DrawRectangleRec({ 0, 0, serverListWidth, (float)screenHeight }, { 30, 30, 30, 255 });

	//Server Icon
	Vector2 iconScale = { (serverListWidth - 20) / ServerIconTexture.width, (serverListWidth - 20) / ServerIconTexture.width };
	DrawTexture(ServerIconTexture, { 10, screenHeight / 2.0f }, { 0, ServerIconTexture.height * iconScale.y / 2.0f }, 0, iconScale, WHITE, false, false);
	DrawRectangleRec({ 0, (screenHeight - ServerIconTexture.height * iconScale.y) / 2, 5, ServerIconTexture.height * iconScale.y }, RAYWHITE);

	//Channel list
	float channelListWidth = 225.0f;
	DrawRectangleRec({ serverListWidth, 0, channelListWidth, (float)screenHeight }, { 45, 45, 45, 255 });

	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		channelButtons[i].Draw();
	}

	//Bars
	float barHeight = 50.0f;

	//Server name
	const char* serverNameText = "New Polynomer's Cou...";
	float serverNameFontSize = BASE_FONT_SIZE / MeasureTextEx(MainFont, serverNameText, BASE_FONT_SIZE, BASE_FONT_SIZE / 10).x * (channelListWidth - 10);
	Vector2 serverNameSize = MeasureTextEx(MainFont, serverNameText, serverNameFontSize, serverNameFontSize / 10);

	DrawTextEx(MainFont, serverNameText, { serverListWidth + 5, barHeight / 2 - serverNameSize.y / 2 }, serverNameFontSize, serverNameFontSize / 10, WHITE);

	DrawLineEx({ serverListWidth, barHeight }, { serverListWidth + channelListWidth, barHeight }, 3.0f, { 10, 10, 10, 255 });

	//User
	DrawRectangleRec({ serverListWidth, screenHeight - barHeight, channelListWidth, barHeight }, { 35, 35, 35, 255 });

	const char* usernameText = "BasementUser123";
	float usernameFontSize = BASE_FONT_SIZE / MeasureTextEx(MainFont, usernameText, BASE_FONT_SIZE, BASE_FONT_SIZE / 10).x * (channelListWidth - 10);

	DrawTextEx(MainFont, usernameText, { serverListWidth + 5, screenHeight - barHeight + barHeight / 2 - usernameFontSize / 2 }, usernameFontSize, usernameFontSize / 10, WHITE);

	//Channel name
	DrawRectangleRec({ serverListWidth + channelListWidth, 0, screenWidth - serverListWidth - channelListWidth, barHeight }, { 50, 50, 50, 255 });

	const char* channelName = GetChannelName(currentChannel);
	float channelNameFontSize = barHeight - 25;

	Vector2 channelIconSize = MeasureTextEx(MainFont, "#", barHeight - 10, 0); //spacing is 0 because this is a singular hashtag lol
	DrawTextEx(MainFont, "#", { serverListWidth + channelListWidth + 5, barHeight / 2 - channelIconSize.y / 2 }, channelIconSize.y, 0, WHITE);

	DrawTextEx(MainFont, channelName, { serverListWidth + channelListWidth + channelIconSize.x + 15, barHeight / 2 - channelNameFontSize / 2 }, channelNameFontSize, channelNameFontSize / 10, WHITE);

	//Channel background
	float channelWidth = screenWidth - serverListWidth - channelListWidth;
	float channelHeight = screenHeight - barHeight;

	DrawRectangleRec(Rectangle{ serverListWidth + channelListWidth, barHeight, channelWidth, channelHeight }, Color{50, 50, 55, 255});
	
	Texture2D& backgroundTexture = GetChannelBackgroundTexture(currentChannel);

	DrawTexture(backgroundTexture, backgroundStartPosition, Vector2{ 0.0f, 0.0f }, 0.0f, Vector2{backgroundScale, backgroundScale}, WHITE, false, false);

	//egg and bunny also scaled by the background scale
	
	//Egg with bunny sometimes idk, also only draw egg in correct channel
	if (currentChannel == eggChannel)
	{
		//only draw egg if not all eggs have been found yet
		if (numFoundEggs != NUM_EGGS)
		{
			Vector2 eggSize = MeasureEgg(Vector2Scale(eggScale, backgroundScale));

			bool isEggHovered = IsEggHovered();
			Color eggTint = numFoundEggs == NUM_EGGS - 1 ? (isEggHovered ? WHITE : LIGHTGRAY) : ColorAlpha(WHITE, isEggHovered ? 1.0f : 0.15f);

			DrawEgg(Eggs[numFoundEggs], Vector2Add(Vector2Scale(eggPosition, backgroundScale), backgroundStartPosition), {eggSize.x / 2, eggSize.y / 2}, 0, Vector2Scale(eggScale, backgroundScale), eggTint);
		}

		//Last egg gets taken by fast bunny!!!
		if (numFoundEggs >= NUM_EGGS - 1)
		{
			float angle = -acosf(bunnyVelocity.x / bunnySpeed);

			if (bunnyVelocity.y < 0)
				angle *= -1;

			Vector2 trueBunnyScale = Vector2Scale(bunnyScale, backgroundScale);
			DrawTexture(BunnyTexture, Vector2Add(Vector2Scale(bunnyPosition, backgroundScale), backgroundStartPosition), { BunnyTexture.width * trueBunnyScale.x / 2.0f,  BunnyTexture.height * trueBunnyScale.y / 2.0f }, 90 - angle * RAD2DEG, trueBunnyScale, deltaBunnyClickTime < 0.25f ? SKYBLUE : (IsBunnyHovered() ? LIGHTGRAY : WHITE), false, false);
		}
	}

	//Draw found eggs on the bottom
	Vector2 benchEggSize = MeasureEgg({ 0.35f * ratioMultiplier, 0.35f * ratioMultiplier });

	for (int i = 0; i < numFoundEggs; i++)
	{
		DrawEgg(Eggs[i], { serverListWidth + channelListWidth + benchEggSize.x * i, (float)screenHeight }, {0, benchEggSize.y}, 0, {0.35f * ratioMultiplier, 0.35f * ratioMultiplier}, {255, 255, 255, 255});
	}
}

const char* GetChannelName(DiscordChannel channel)
{
	switch (channel)
	{
		case DISCORD_CHANNEL_GENARAL:
			return "genaral";
		case DISCORD_CHANNEL_GENERAL_2:
			return "general-2";
		case DISCORD_CHANNEL_FISHING_LAKE:
			return "fishing-lake";
		case DISCORD_CHANNEL_STOCK_MARKET_BOAT:
			return "stock-market-boat";
		case DISCORD_CHANNEL_THE_BUS:
			return "the-bus";
		default:
			return "illegal-channel-lol";
	}
}

//I know I probably shouldn't be doing this, but I need to get this finished before the polyjam ends and I don't know how to copy char* without causing issues
const char* GetChannelNameTag(DiscordChannel channel)
{
	switch (channel)
	{
		case DISCORD_CHANNEL_GENARAL:
			return "#genaral";
		case DISCORD_CHANNEL_GENERAL_2:
			return "#general-2";
		case DISCORD_CHANNEL_FISHING_LAKE:
			return "#fishing-lake";
		case DISCORD_CHANNEL_STOCK_MARKET_BOAT:
			return "#stock-market-boat";
		case DISCORD_CHANNEL_THE_BUS:
			return "#the-bus";
		default:
			return "#illegal-channel-lol";
	}
}

Texture2D& GetChannelBackgroundTexture(DiscordChannel channel)
{
	switch (channel)
	{
		case DISCORD_CHANNEL_GENARAL:
			return Channel_GenaralTexture;
		case DISCORD_CHANNEL_GENERAL_2:
			return Channel_General2Texture;
		case DISCORD_CHANNEL_FISHING_LAKE:
			return Channel_FishingLakeTexture;
		case DISCORD_CHANNEL_STOCK_MARKET_BOAT:
			return Channel_StockMarketBoatTexture;
		case DISCORD_CHANNEL_THE_BUS:
			return Channel_TheBusTexture;
		default:
			throw (channel);
	}
}