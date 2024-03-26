#include "UIUtils.h"

bool IsRectHovered(Rectangle rect, Camera2D camera)
{
	Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

	return mouseWorldPos.x >= rect.x && mouseWorldPos.x <= rect.x + rect.width && mouseWorldPos.y >= rect.y && mouseWorldPos.y <= rect.y + rect.height;
}