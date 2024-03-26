#include "Statebox.h"
#include "UIUtils.h"

void Statebox::UpdateStatebox(Camera2D camera)
{
	if (Released)
	{
		//Reverse state
		State = !State;
	}
}