#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "elements/TextButton.h"
#include "eggCreator.h"
#include "game.h"
#include "assets.h"
#include "Eggventure.h"

int eggIndex = 0;
TextButton nextButton = TextButton();

void EggCreatorInit()
{
	eggIndex = 0;

	nextButton.TextFont = MainFont;
	nextButton.Text = "NEXT";
	nextButton.Background = IconButton_Background;
	nextButton.BackgroundNPatchInfo = IconButton_Background_NPatch;
}

void EggCreatorUpdate()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	float benchHeight = 30 * ratioMultiplier;
	float eggEditorHeight = 150 * ratioMultiplier;

	nextButton.FontSize = 48 * ratioMultiplier;
	nextButton.Spacing = 4.8F * ratioMultiplier;
	nextButton.Padding = 8.0F * ratioMultiplier;
	nextButton.FitText();
	nextButton.MoveTo({screenWidth - nextButton.Rect.width - 30 * ratioMultiplier, screenHeight - benchHeight - eggEditorHeight - nextButton.Rect.height});

	nextButton.Update(MainCamera);

	if (nextButton.Released && eggIndex != NUM_EGGS - 1)
	{
		std::cout << "Next egg" << std::endl;
		eggIndex++;

		if (eggIndex == NUM_EGGS - 1)
		{
			nextButton.Text = "Finish";

			nextButton.FitText();
			nextButton.MoveTo({ screenWidth - nextButton.Rect.width - 30 * ratioMultiplier, screenHeight - benchHeight - eggEditorHeight - nextButton.Rect.height });
		}
	}
	else if (nextButton.Released && eggIndex == NUM_EGGS - 1)
	{
		std::cout << "Finished" << std::endl;
		SetGameState(EggHiding);
	}

}

void EggCreatorDraw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, ORANGE, RED, RED, ORANGE);
	
	float benchHeight = 30 * ratioMultiplier;
	float eggEditorHeight = 150 * ratioMultiplier;

	Vector2 eggScale = { 2, 2 };
	Vector2 eggSize = MeasureEgg(eggScale);
	
	DrawEgg(Eggs[eggIndex], { (float)screenWidth / 2, (float)(screenHeight - eggEditorHeight) / 2 }, { eggSize.x / 2, eggSize.y / 2 }, 0, eggScale, WHITE);

	DrawRectangleRec({ 0, screenHeight - eggEditorHeight - benchHeight, (float)screenWidth, eggEditorHeight + benchHeight}, RAYWHITE);

	nextButton.Draw();

	EndDrawing();
}