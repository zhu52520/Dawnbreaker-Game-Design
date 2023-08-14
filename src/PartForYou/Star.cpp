#include "Star.h"
#include "utils.h"

Star::Star(int x, int y, double size) : GameObject(IMGID_STAR, x, y, 0, 4, size){};

void Star::Update()
{
    if (GetY() < 0)
    {
        SetDeath();
    }
    MoveTo(GetX(), GetY() - 1);
}