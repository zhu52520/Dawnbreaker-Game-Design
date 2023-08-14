#include "Bullet.h"

Bullet::Bullet(int imageID, int x, int y, double size, int damage, int direction, GameWorld *world) : GameObject(imageID, x, y, direction, 1, size), m_damage(damage), m_world(world) {}

void Bullet::Update()
{
    if (IsDeath())
	{
		return;
	}
    if ((GetY() < 0) || (GetY() >= WINDOW_HEIGHT))
    {
        SetDeath();
        return;
    }
    if (!IsDeath() && m_world->HitEnemy(m_damage, this))
    {
        afterHit();
    }
    if (!IsDeath())
    {
        move();
    }
    if (!IsDeath() && m_world->HitEnemy(m_damage, this))
    {
        afterHit();
    }
}

GameWorld *Bullet::GetWorld()
{
    return m_world;
}

int Bullet::GetDamage()
{
    return m_damage;
}

BlueBullet::BlueBullet(int x, int y, double size, int damage, GameWorld *world) : Bullet(IMGID_BLUE_BULLET, x, y, size, damage, 0, world) { SetMyBullet(); }

void BlueBullet::afterHit()
{
    SetDeath();
}

void BlueBullet::move()
{
    MoveTo(GetX(), GetY() + 6);
}

Meteor::Meteor(int x, int y, GameWorld *world) : Bullet(IMGID_METEOR, x, y, 2.0, 9999999, 0, world) {SetMyBullet();}

void Meteor::afterHit()
{
    return;
}

void Meteor::move()
{
    MoveTo(GetX(), GetY() + 2);
    SetDirection(GetDirection() + 5);
}

RedBullet::RedBullet(int x, int y, int damage, int direction, GameWorld *world) : Bullet(IMGID_RED_BULLET, x, y, 0.5, damage, direction, world) {SetEnemyBullet();}

void RedBullet::Update()
{
    if (IsDeath())
	{
		return;
	}
    if (GetY() < 0)
    {
        SetDeath();
        return;
    }
    if (GetWorld()->HitDawn(GetDamage(), this))
    {
        afterHit();
        return;
    }
    move();
    if (GetWorld()->HitDawn(GetDamage(), this))
    {
        afterHit();
    }
}

void RedBullet::afterHit()
{
    SetDeath();
}

void RedBullet::move()
{
    if (GetDirection() == 180)
    {
        MoveTo(GetX(), GetY() - 6);
    }
    else if (GetDirection() == 162)
    {
        MoveTo(GetX() + 2, GetY() - 6);
    }
    else
    {
        MoveTo(GetX() - 2, GetY() - 6);
    }
}
