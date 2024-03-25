#pragma once

enum GameState
{
	Intro,
	EggCreation,
	EggHiding,
	EggHunt
};

void GameUpdate();

void IntroDraw();
