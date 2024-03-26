#include "Statebox.h"
#include "UIUtils.h"

void Statebox::Update(Camera2D camera)
{
	Button::Update(camera);

	ChangedThisFrame = false;

	if (IsRectHovered(Rect, camera) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		//Reverse state
		State = !State;

		ChangedThisFrame = true;
	}
}