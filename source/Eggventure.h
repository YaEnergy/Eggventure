﻿// Eggventure.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "raylib.h"
// TODO: Reference additional headers your program requires here.

#ifdef WIN32RELEASE
	int main();
#endif // RELEASE


void UpdateDrawFrame();

float GetScreenDesignRatioMultiplier();