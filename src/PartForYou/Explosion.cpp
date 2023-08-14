#include "Explosion.h"

Explosion::Explosion(int x, int y) :GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5), count(0) {}

void Explosion::Update()
{
	SetSize(GetSize() - 0.2);
	count++;
	if (count == 20)
	{
		SetDeath();
	}
}