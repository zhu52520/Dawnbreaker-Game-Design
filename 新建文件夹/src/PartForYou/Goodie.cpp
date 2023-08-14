#include "Goodie.h"

Goodie::Goodie(int imageID, int x, int y, GameObject *dawnbreaker) : GameObject(imageID, x, y, 0, 2, 0.5), m_dawnbreaker(dawnbreaker) {}

void Goodie::Update()
{
    if (GetY() < 0)
    {
        SetDeath();
    }
    if (!IsDeath())
    {
        if (IsCollision(m_dawnbreaker, this))
        {
            collided();
        }
        else
        {
            MoveTo(GetX(), GetY() - 2);
            if (IsCollision(m_dawnbreaker, this))
            {
                collided();
            }
        }
    }
}

RestoreGoodie::RestoreGoodie(int x, int y, GameObject *dawnbreaker) : Goodie(IMGID_HP_RESTORE_GOODIE, x, y, dawnbreaker) {}

void RestoreGoodie::collided()
{
    m_dawnbreaker->restore(50);
    SetDeath();
}

PowerGoodie::PowerGoodie(int x, int y, GameObject *dawnbreaker) : Goodie(IMGID_POWERUP_GOODIE, x, y, dawnbreaker) {}

void PowerGoodie::collided()
{
    m_dawnbreaker->powerup(1);
    SetDeath();
}

MeteorGoodie::MeteorGoodie(int x, int y, GameObject *dawnbreaker) : Goodie(IMGID_METEOR_GOODIE, x, y, dawnbreaker) {}

void MeteorGoodie::collided()
{
    m_dawnbreaker->meteorup(1);
    SetDeath();
}