#include "eggHunt.h"
#include "assets.h"
#include "renderer.h"
#include "egg.h"
#include "game.h"
#include "Eggventure.h"
#include "elements/TextButton.h"
#include "elements/UIUtils.h"

const float BASE_FONT_SIZE = 16.0f;

const int NUM_CHANNELS = 5;

enum DiscordChannel
{
	DISCORD_CHANNEL_GENARAL, //Best channel name
	DISCORD_CHANNEL_GENERAL_2,
	DISCORD_CHANNEL_FISHING_LAKE,
	DISCORD_CHANNEL_STOCK_MARKET_BOAT,
	DISCORD_CHANNEL_THE_BUS,
};

int numFoundEggs = 0;
Vector2 eggScale = { 0.25f, 0.25f };
Vector2 eggPosition = { 0, 0 };
DiscordChannel eggChannel = DISCORD_CHANNEL_GENARAL;

Vector2 bunnyPosition = { 0, 0 };
Vector2 bunnyScale = { 0.5f, 0.5f };
Vector2 bunnyVelocity = { 0, 0 };
float bunnySpeed = 200;

int bunnyClicksLeft = 3;
float deltaBunnyClickTime = 0.0f;

DiscordChannel currentChannel = DISCORD_CHANNEL_GENARAL;

TextButton channelButtons[NUM_CHANNELS] = { TextButton(), TextButton(), TextButton(), TextButton(), TextButton() };

bool IsEggHovered();
void ChangeChannel(DiscordChannel channel);
void RandomHideEgg();
const char* GetChannelName(DiscordChannel channel);
Texture2D GetChannelBackgroundTexture(DiscordChannel channel);

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
		channelButtons[i].Text = GetChannelName((DiscordChannel)i); //add hashtag infront of here
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
	bunnyClicksLeft = 3;
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

	Vector2 eggSize = MeasureEgg(eggScale);

	// bunny egg movement
	if (numFoundEggs == NUM_EGGS - 1 && currentChannel == eggChannel)
	{
		float deltaTime = GetFrameTime();

		deltaBunnyClickTime += deltaTime;

		bunnyPosition = { bunnyPosition.x + bunnyVelocity.x * deltaTime, bunnyPosition.y + bunnyVelocity.y * deltaTime };

		//collision stuff here
		bool isCollidingX = false;
		float collisionX = 0;

		if (bunnyPosition.x > screenWidth - BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionX = (screenWidth - BunnyTexture.width * bunnyScale.x / 2.0f);
			isCollidingX = true;
		}
		else if (bunnyPosition.x < serverListWidth + channelListWidth + BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionX = serverListWidth + channelListWidth + BunnyTexture.width * bunnyScale.x / 2.0f;
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

		if (bunnyPosition.y > screenHeight - BunnyTexture.height * bunnyScale.y / 2.0f)
		{
			collisionY = screenHeight - BunnyTexture.height * bunnyScale.y / 2.0f;
			isCollidingY = true;
		}
		else if (bunnyPosition.y < barHeight + BunnyTexture.width * bunnyScale.x / 2.0f)
		{
			collisionY = barHeight + BunnyTexture.width * bunnyScale.x / 2.0f;
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

	//Check if egg is clicked and found
	if (IsEggHovered() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (numFoundEggs == NUM_EGGS - 1 && bunnyClicksLeft > 0)
		{
			bunnyClicksLeft--;

			//Double bunny speed
			bunnySpeed *= 2;
			bunnyVelocity = { bunnyVelocity.x * 2, bunnyVelocity.y * 2 };

			deltaBunnyClickTime = 0.0f;
		}
		else
		{
			numFoundEggs++;
			RandomHideEgg();
		}
	}

	//If all eggs have been found
	if (numFoundEggs == NUM_EGGS)
	{
		SetGameState(Win);
	}
}

bool IsEggHovered()
{
	Vector2 eggSize = MeasureEgg(eggScale);
	return IsRectHovered({ eggPosition.x - eggSize.x / 2, eggPosition.y - eggSize.y / 2,  eggSize.x, eggSize.y }, MainCamera);
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
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//mmm i love copying values over, allowing me to make changes and forgetting to make them somewhere else
	float barHeight = 50.0f;
	float serverListWidth = 75.0f;
	float channelListWidth = 225.0f;

	Vector2 eggSize = MeasureEgg(eggScale);
	Vector2 benchEggSize = MeasureEgg({ 0.35f * ratioMultiplier, 0.35f * ratioMultiplier });

	eggPosition = { (float)GetRandomValue((int)(serverListWidth + channelListWidth + eggSize.x / 2), (int)(screenWidth - eggSize.x / 2)), (float)GetRandomValue((int)(barHeight) + eggSize.y / 2, (int)(screenHeight - eggSize.y / 2 - benchEggSize.y)) };
	bunnyPosition = eggPosition;

	//Random channel, just not the current egg channel

	DiscordChannel oldChannel = eggChannel;

	while (oldChannel == eggChannel)
	{
		eggChannel = (DiscordChannel)GetRandomValue(0, NUM_CHANNELS - 1);
	}
}

void EggHuntDraw()
{
	BeginDrawing();

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
	Texture2D backgroundTexture = GetChannelBackgroundTexture(currentChannel);
	DrawTexture(backgroundTexture, { serverListWidth + channelListWidth, barHeight }, { 0, 0 }, 0, { 1, 1 }, WHITE, false, false);

	//Egg with bunny sometimes idk
	if (currentChannel == eggChannel)
	{
		Vector2 eggScale = { 0.25f * ratioMultiplier, 0.25f * ratioMultiplier };
		Vector2 eggSize = MeasureEgg(eggScale);

		bool isEggHovered = IsEggHovered();
		Color eggTint = numFoundEggs == NUM_EGGS - 1 ? (isEggHovered ? WHITE : LIGHTGRAY) : ColorAlpha(WHITE, isEggHovered ? 1.0f : 0.15f);

		DrawEgg(Eggs[numFoundEggs], eggPosition, {eggSize.x / 2, eggSize.y / 2}, 0, eggScale, eggTint);

		//Last egg gets taken by fast bunny!!!
		if (numFoundEggs == NUM_EGGS - 1)
		{
			float angle = -acosf(bunnyVelocity.x / bunnySpeed);

			if (bunnyVelocity.y < 0)
				angle *= -1;

			DrawTexture(BunnyTexture, bunnyPosition, { BunnyTexture.width * bunnyScale.x / 2.0f,  BunnyTexture.height * bunnyScale.y / 2.0f }, 90 - angle * RAD2DEG, bunnyScale, deltaBunnyClickTime < 0.25f ? SKYBLUE : WHITE, false, false);
		}
	}

	//Draw found eggs on the bottom
	Vector2 benchEggSize = MeasureEgg({ 0.35f * ratioMultiplier, 0.35f * ratioMultiplier });

	for (int i = 0; i < numFoundEggs; i++)
	{
		DrawEgg(Eggs[i], { serverListWidth + channelListWidth + benchEggSize.x * i, (float)screenHeight }, {0, benchEggSize.y}, 0, {0.35f * ratioMultiplier, 0.35f * ratioMultiplier}, {255, 255, 255, 255});
	}

	EndDrawing();
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

Texture2D GetChannelBackgroundTexture(DiscordChannel channel)
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
	}
}