#pragma once

#include "raylib.h"
#include "egg.h"

const int NUM_EGGS = 3;

enum GameState
{
	Intro,
	EggCreation,
	EggHiding,
	EggHunt
};

extern Camera2D MainCamera;
extern Egg Eggs[];

void InitGame();
void GameUpdate();
void SetGameState(GameState state);