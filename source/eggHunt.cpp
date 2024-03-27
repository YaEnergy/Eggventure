#include "eggHunt.h"
#include "assets.h"
#include "renderer.h"
#include "egg.h"
#include "game.h"
#include "Eggventure.h"
#include "elements/UIUtils.h"

int numFoundEggs = 0;
Vector2 eggPosition = { 0, 0 };
DiscordChannel eggChannel = DISCORD_CHANNEL_GENARAL;

DiscordChannel currentChannel = DISCORD_CHANNEL_GENARAL;

const char* GetChannelName(DiscordChannel channel);

void EggHuntInit()
{
	//do some randomisation crap here or something idk
}

void EggHuntUpdate()
{
	//Update channel buttons
	//and channel

	//Check if egg is clicked and found
}

void EggHuntDraw()
{
	BeginDrawing();

	ClearBackground(WHITE);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();
	const float BASE_FONT_SIZE = 16.0f;

	//Channel background

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

	//Egg with bunny sometimes idk

	EndDrawing();
}

const char* GetChannelName(DiscordChannel channel)
{
	switch (currentChannel)
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