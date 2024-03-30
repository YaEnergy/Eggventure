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
EggStatebox designStateboxes[EGG_DESIGNS_NUM - 1] = { };

//Marks
EggStatebox markStateboxes[EGG_MARKS_NUM - 1] = { };

const int CHOOSEABLE_COLORS_NUM = 10;

//Base Colors
EggStatebox baseColorStateboxes[CHOOSEABLE_COLORS_NUM] = { };

//Design Colors
EggStatebox designColorStateboxes[CHOOSEABLE_COLORS_NUM] = { };

//Mark Colors
EggStatebox markColorStateboxes[CHOOSEABLE_COLORS_NUM] = { };

bool AreColorsEqual(Color color1, Color color2);

void SetEggIndex(int index);
void SetEggDesign(EggDesign design);
void SetEggMark(EggMark mark);
void SetEggBaseColor(Color color);
void SetEggDesignColor(Color color);
void SetEggMarkColor(Color color);

void EggCreatorInit()
{
	nextButton.TextFont = MainFont;
	nextButton.Text = "NEXT";
	nextButton.Background = IconButton_Background;
	nextButton.BackgroundNPatchInfo = IconButton_Background_NPatch;

	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i] = EggStatebox();

		designStateboxes[i].Background = IconButton_Background;
		designStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		designStateboxes[i].BoxEgg.design = (EggDesign)i;
		designStateboxes[i].BoxEgg.mark = NoEggMark;
		designStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		designStateboxes[i].BoxEgg.markColor = GRAY;
		designStateboxes[i].BoxEgg.baseColor = WHITE;
	}

	for (int i = 0; i < EGG_MARKS_NUM - 1; i++)
	{
		markStateboxes[i] = EggStatebox();

		markStateboxes[i].Background = IconButton_Background;
		markStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		markStateboxes[i].BoxEgg.design = NoEggDesign;
		markStateboxes[i].BoxEgg.mark = (EggMark)i;
		markStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		markStateboxes[i].BoxEgg.markColor = GRAY;
		markStateboxes[i].BoxEgg.baseColor = WHITE;
	}

	Color colors[CHOOSEABLE_COLORS_NUM] = { RED, BLUE, GREEN, YELLOW, PINK, PURPLE, ORANGE, SKYBLUE, BLACK, WHITE };

	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		//Base color
		baseColorStateboxes[i] = EggStatebox();

		baseColorStateboxes[i].Background = IconButton_Background;
		baseColorStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		baseColorStateboxes[i].BoxEgg.design = NoEggDesign;
		baseColorStateboxes[i].BoxEgg.mark = NoEggMark;
		baseColorStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		baseColorStateboxes[i].BoxEgg.markColor = GRAY;
		baseColorStateboxes[i].BoxEgg.baseColor = colors[i];

		//Design color
		designColorStateboxes[i] = EggStatebox();

		designColorStateboxes[i].Background = IconButton_Background;
		designColorStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		designColorStateboxes[i].BoxEgg.design = NoEggDesign;
		designColorStateboxes[i].BoxEgg.mark = NoEggMark;
		designColorStateboxes[i].BoxEgg.designColor = colors[i];
		designColorStateboxes[i].BoxEgg.markColor = GRAY;
		designColorStateboxes[i].BoxEgg.baseColor = LIGHTGRAY;

		//Mark color
		markColorStateboxes[i] = EggStatebox();

		markColorStateboxes[i].Background = IconButton_Background;
		markColorStateboxes[i].BackgroundNPatchInfo = IconButton_Background_NPatch;

		markColorStateboxes[i].BoxEgg.design = NoEggDesign;
		markColorStateboxes[i].BoxEgg.mark = NoEggMark;
		markColorStateboxes[i].BoxEgg.designColor = LIGHTGRAY;
		markColorStateboxes[i].BoxEgg.markColor = colors[i];
		markColorStateboxes[i].BoxEgg.baseColor = LIGHTGRAY;
	}

	SetEggIndex(eggIndex);
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
		PlaySound(SFX_Start);
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
		PlaySound(SFX_Start);
		SetGameState(EggHiding);
	}

	//Editor
	Vector2 editorEggScale = { 0.3f * ratioMultiplier, 0.3f * ratioMultiplier };
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
			PlaySound(SFX_EggEditorSelect);
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
			PlaySound(SFX_EggEditorSelect);
			SetEggMark(markStateboxes[i].State ? markStateboxes[i].BoxEgg.mark : NoEggMark);
		}
	}

	//Egg base colors
	float baseColorEggSpace = boxWidth + 5 * ratioMultiplier;

	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		baseColorStateboxes[i].EggScale = editorEggScale;
		baseColorStateboxes[i].Rect = { (screenWidth + baseColorEggSpace * CHOOSEABLE_COLORS_NUM) / 2 - 5 * ratioMultiplier - baseColorEggSpace * (i + 1), screenHeight - eggEditorHeight + boxHeight * 2 + 35 * ratioMultiplier, boxWidth, boxHeight };

		baseColorStateboxes[i].UpdateButton(MainCamera);
		baseColorStateboxes[i].UpdateStatebox(MainCamera);

		if (baseColorStateboxes[i].Released)
		{
			PlaySound(SFX_EggEditorSelect);
			SetEggBaseColor(baseColorStateboxes[i].State ? baseColorStateboxes[i].BoxEgg.baseColor : WHITE);
		}
	}

	//Egg design colors
	if (Eggs[eggIndex].design != NoEggDesign)
	{
		for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
		{
			designColorStateboxes[i].EggScale = editorEggScale;
			designColorStateboxes[i].Rect = { screenWidth - 5 * ratioMultiplier - (boxWidth + 5 * ratioMultiplier) * (i + 1), screenHeight - eggEditorHeight + 15 * ratioMultiplier, boxWidth, boxHeight };

			designColorStateboxes[i].UpdateButton(MainCamera);
			designColorStateboxes[i].UpdateStatebox(MainCamera);

			if (designColorStateboxes[i].Released)
			{
				PlaySound(SFX_EggEditorSelect);
				SetEggDesignColor(designColorStateboxes[i].State ? designColorStateboxes[i].BoxEgg.designColor : LIGHTGRAY);
			}
		}
	}

	//Egg mark colors
	if (Eggs[eggIndex].mark != NoEggMark)
	{
		for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
		{
			markColorStateboxes[i].EggScale = editorEggScale;
			markColorStateboxes[i].Rect = { screenWidth - 5 * ratioMultiplier - (boxWidth + 5 * ratioMultiplier) * (i + 1), screenHeight - eggEditorHeight + boxHeight + 25 * ratioMultiplier, boxWidth, boxHeight };

			markColorStateboxes[i].UpdateButton(MainCamera);
			markColorStateboxes[i].UpdateStatebox(MainCamera);

			if (markColorStateboxes[i].Released)
			{
				PlaySound(SFX_EggEditorSelect);
				SetEggMarkColor(markColorStateboxes[i].State ? markColorStateboxes[i].BoxEgg.markColor : GRAY);
			}
		}
	}

	//Music
	if (!IsMusicStreamPlaying(Music_Main))
	{
		PlayMusicStream(Music_Main);
	}

	UpdateMusicStream(Music_Main);
}

bool AreColorsEqual(Color color1, Color color2)
{
	//Two colors are equal if they have the same values
	return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a;
}

void SetEggIndex(int index)
{
	eggIndex = index;

	SetEggDesign(Eggs[eggIndex].design);
	SetEggMark(Eggs[eggIndex].mark);
	SetEggBaseColor(Eggs[eggIndex].baseColor);
	SetEggDesignColor(Eggs[eggIndex].designColor);
	SetEggMarkColor(Eggs[eggIndex].markColor);
}

void SetEggDesign(EggDesign design)
{
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		designStateboxes[i].State = designStateboxes[i].BoxEgg.design == design;
	}

	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		designColorStateboxes[i].BoxEgg.design = design;
	}

	Eggs[eggIndex].design = design;
}

void SetEggMark(EggMark mark)
{
	for (int i = 0; i < EGG_DESIGNS_NUM - 1; i++)
	{
		markStateboxes[i].State = markStateboxes[i].BoxEgg.mark == mark;
	}
	
	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		markColorStateboxes[i].BoxEgg.mark = mark;
	}

	Eggs[eggIndex].mark = mark;
}

void SetEggBaseColor(Color color)
{
	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		baseColorStateboxes[i].State = AreColorsEqual(baseColorStateboxes[i].BoxEgg.baseColor, color);
	}

	Eggs[eggIndex].baseColor = color;
}

void SetEggDesignColor(Color color)
{
	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		designColorStateboxes[i].State = AreColorsEqual(designColorStateboxes[i].BoxEgg.designColor, color);
	}

	Eggs[eggIndex].designColor = color;
}

void SetEggMarkColor(Color color)
{
	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		markColorStateboxes[i].State = AreColorsEqual(markColorStateboxes[i].BoxEgg.markColor, color);
	}

	Eggs[eggIndex].markColor = color;
}


void EggCreatorDraw()
{
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

	for (int i = 0; i < CHOOSEABLE_COLORS_NUM; i++)
	{
		baseColorStateboxes[i].Draw();

		if (Eggs[eggIndex].design != NoEggDesign)
		{
			designColorStateboxes[i].Draw();
		}

		if (Eggs[eggIndex].mark != NoEggMark)
		{
			markColorStateboxes[i].Draw();
		}
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

	//TODO: change this, this is bad
	const char* eggNumText = TextFormat("Egg %01i/%01i", eggIndex + 1, NUM_EGGS);

	float eggNumFontSize = 24 * ratioMultiplier;
	Vector2 eggNumSize = MeasureTextEx(MainFont, eggNumText, eggNumFontSize, eggNumFontSize / 10);
	DrawTextEx(MainFont, eggNumText, { (screenWidth - eggNumSize.x) / 2, titleFontSize / 2 + titleSize.y }, eggNumFontSize, eggNumFontSize / 10, WHITE);
}