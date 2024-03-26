#include "raylib.h"
#include "renderer.h"
#include "egg.h"
#include "elements/TextButton.h"
#include "eggCreator.h"
#include "EggStatebox.h"
#include "game.h"
#include "assets.h"
#include "Eggventure.h"

int eggIndex = 0;

TextButton nextButton = TextButton();

//Designs
EggStatebox designStateboxes[EGG_DESIGNS_NUM - 1] = { EggStatebox(), EggStatebox(), EggStatebox() };

//Marks
EggStatebox markStateboxes[EGG_MARKS_NUM - 1] = { EggStatebox(), EggStatebox(), EggStatebox() };

//TODO: implement color state boxes

//Design Colors
//EggStatebox designColorStateboxes[5] = { EggStatebox(), EggStatebox(), EggStatebox(), EggStatebox(), EggStatebox() };

//Mark Colors
//EggStatebox markColorStateboxes[5] = { EggStatebox(), EggStatebox(), EggStatebox(), EggStatebox(), EggStatebox() };

void SetEggIndex(int index);
void SetEggDesign(EggDesign design);
void SetEggMark(EggMark mark);

void EggCreatorInit()
{
	nextButton.TextFont = MainFont;
	nextButton.Text = "NEXT";
	nextButton.Background = IconButton_Background;
	nextButton.BackgroundNPatchInfo = IconButton_Background_NPatch;

	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i].Background = IconButton_Background;
		designStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		designStateboxes[i].BoxEgg.mark = NoEggMark;
		designStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		designStateboxes[i].BoxEgg.markColor = GRAY;
		designStateboxes[i].BoxEgg.baseColor = WHITE;
	}

	designStateboxes[0].BoxEgg.design = SpikyStripes;
	designStateboxes[1].BoxEgg.design = WavyStripes;
	designStateboxes[2].BoxEgg.design = StraightStripes;

	for (int i = 0; i < EGG_MARKS_NUM - 1; i++)
	{
		markStateboxes[i].Background = IconButton_Background;
		markStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		markStateboxes[i].BoxEgg.design = NoEggDesign;
		markStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		markStateboxes[i].BoxEgg.markColor = GRAY;
		markStateboxes[i].BoxEgg.baseColor = WHITE;
	}

	markStateboxes[0].BoxEgg.mark = CatFace;
	markStateboxes[1].BoxEgg.mark = Star;
	markStateboxes[2].BoxEgg.mark = Circle;

	SetEggIndex(0);
}

void EggCreatorUpdate()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	float eggEditorHeight = 180 * ratioMultiplier;

	nextButton.FontSize = 48 * ratioMultiplier;
	nextButton.Spacing = 4.8F * ratioMultiplier;
	nextButton.Padding = 8.0F * ratioMultiplier;
	nextButton.FitText();
	nextButton.MoveTo({screenWidth - nextButton.Rect.width - 30 * ratioMultiplier, screenHeight - eggEditorHeight - nextButton.Rect.height});

	nextButton.UpdateButton(MainCamera);

	if (nextButton.Released && eggIndex != NUM_EGGS - 1)
	{
		std::cout << "Next egg" << std::endl;
		SetEggIndex(eggIndex + 1);

		if (eggIndex == NUM_EGGS - 1)
		{
			nextButton.Text = "Finish";

			nextButton.FitText();
			nextButton.MoveTo({ screenWidth - nextButton.Rect.width - 30 * ratioMultiplier, screenHeight - eggEditorHeight - nextButton.Rect.height });
		}
	}
	else if (nextButton.Released && eggIndex == NUM_EGGS - 1)
	{
		std::cout << "Finished" << std::endl;
		SetGameState(EggHiding);
	}

	//Editor
	Vector2 editorEggScale = { 0.5f * ratioMultiplier, 0.5f * ratioMultiplier };
	Vector2 editorEggSize = MeasureEgg(editorEggScale);

	float boxWidth = editorEggSize.x + 15 * ratioMultiplier;
	float boxHeight = editorEggSize.y + 15 * ratioMultiplier;

	//Egg designs
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i].EggScale = editorEggScale;
		designStateboxes[i].Rect = { 5 * ratioMultiplier + (boxWidth + 5 * ratioMultiplier) * i, screenHeight - eggEditorHeight + 15 * ratioMultiplier, boxWidth, boxHeight };
		
		designStateboxes[i].UpdateButton(MainCamera);
		designStateboxes[i].UpdateStatebox(MainCamera);

		if (designStateboxes[i].Released)
		{
			SetEggDesign(designStateboxes[i].State ? designStateboxes[i].BoxEgg.design : NoEggDesign);
		}
	}

	//Egg marks
	for (int i = 0; i < EGG_MARKS_NUM - 1; i++)
	{
		markStateboxes[i].EggScale = editorEggScale;
		markStateboxes[i].Rect = { 5 * ratioMultiplier + (boxWidth + 5 * ratioMultiplier) * i, screenHeight - eggEditorHeight + boxHeight + 25 * ratioMultiplier, boxWidth, boxHeight };
		
		markStateboxes[i].UpdateButton(MainCamera);
		markStateboxes[i].UpdateStatebox(MainCamera);

		if (markStateboxes[i].Released)
		{
			SetEggMark(markStateboxes[i].State ? markStateboxes[i].BoxEgg.mark : NoEggMark);
		}
	}
}

void SetEggIndex(int index)
{
	eggIndex = index;

	SetEggDesign(Eggs[eggIndex].design);
	SetEggMark(Eggs[eggIndex].mark);
}

void SetEggDesign(EggDesign design)
{
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i].State = designStateboxes[i].BoxEgg.design == design;
	}

	Eggs[eggIndex].design = design;
}

void SetEggMark(EggMark mark)
{
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		markStateboxes[i].State = markStateboxes[i].BoxEgg.mark == mark;
	}

	Eggs[eggIndex].mark = mark;
}

void EggCreatorDraw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	float ratioMultiplier = GetScreenDesignRatioMultiplier();

	float eggEditorHeight = 180 * ratioMultiplier;

	//Background
	Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };
	DrawRectangleGradientEx(screenRect, ORANGE, RED, RED, ORANGE);


	//Editor
	DrawRectangleRec({ 0, screenHeight - eggEditorHeight, (float)screenWidth, eggEditorHeight}, RAYWHITE);

	//Next button
	nextButton.Draw();

	//Egg state boxes
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i].Draw();
	}

	for (int i = 0; i < EGG_MARKS_NUM - 1; i++)
	{
		markStateboxes[i].Draw();
	}

	//Current egg
	Vector2 eggScale = { 1.5f * ratioMultiplier, 1.5f * ratioMultiplier };
	Vector2 eggSize = MeasureEgg(eggScale);
	
	DrawEgg(Eggs[eggIndex], { (float)screenWidth / 2, (float)(screenHeight - eggEditorHeight) / 2 + 30 * ratioMultiplier }, { eggSize.x / 2, eggSize.y / 2 }, 0, eggScale, WHITE);

	//Created eggs on bench
	for (int i = 0; i < eggIndex; i++)
	{
		Vector2 benchEggScale = { 0.5f * ratioMultiplier, 0.5f * ratioMultiplier };
		Vector2 benchEggSize = MeasureEgg(benchEggScale);

		DrawEgg(Eggs[i], { 5 * ratioMultiplier + (benchEggSize.x + 5 * ratioMultiplier) * i, screenHeight - eggEditorHeight }, { 0, benchEggSize.y }, 0, benchEggScale, WHITE);
	}

	//Title
	const char* titleText = "Create eggs!";
	float titleFontSize = 36 * ratioMultiplier;
	Vector2 titleSize = MeasureTextEx(MainFont, titleText, titleFontSize, titleFontSize / 10);
	DrawTextEx(MainFont, titleText, { (screenWidth - titleSize.x) / 2, titleFontSize / 2 }, titleFontSize, titleFontSize / 10, WHITE);

	const char* eggNumText = TextFormat("Egg %01i/%01i", eggIndex + 1, NUM_EGGS);
	float eggNumFontSize = 24 * ratioMultiplier;
	Vector2 eggNumSize = MeasureTextEx(MainFont, eggNumText, eggNumFontSize, eggNumFontSize / 10);
	DrawTextEx(MainFont, eggNumText, { (screenWidth - eggNumSize.x) / 2, titleFontSize / 2 + titleSize.y }, eggNumFontSize, eggNumFontSize / 10, WHITE);


	EndDrawing();
}