#include "Enemy.h"
#include "Bullet.h"
#include "Goodie.h"

Enemy::Enemy(int imageID, int x, int y, int health, int damage, int energy, int speed, GameWorld *world) : GameObject(imageID, x, y, 180, 0, 1.0), m_health(health), attack(damage), m_energy(energy), speed(speed), m_world(world), flymethod(0), flytime(0), energy_max(energy)
{
	SetEnemy();
}

void Enemy::BeingHit(int damage)
{
	m_health -= damage;
	if (m_health <= 0 && !IsDeath())
	{
		Dead();
	}
}

void Enemy::Update()
{
	if (IsDeath())
	{
		return;
	}
	if (GetY() < 0)
	{
		SetDeath();
		m_world->DecreaseOnScreen();
	}
	if (IsDeath())
	{
		return;
	}
	if (m_world->CollideDawn(this))
	{
		Dead();
	}
	if (IsDeath())
	{
		return;
	}
	m_world->EnemyBeHit(this);
	if (IsDeath())
	{
		return;
	}

	Attack();

	if (m_energy < energy_max)
	{
		m_energy += 1;
	}

	Move();
	if (m_world->CollideDawn(this))
	{
		Dead();
	}
	if (IsDeath())
	{ 
		return;
	}
	m_world->EnemyBeHit(this);
}

void Enemy::Move()
{
	if (flytime == 0)
	{
		flymethod = randInt(0, 2);
		flytime = randInt(10, 50);
	}
	if (GetX() < 0)
	{
		flymethod = 2;
		flytime = randInt(10, 50);
	}
	else if (GetX() >= WINDOW_WIDTH)
	{
		flymethod = 0;
		flytime = randInt(10, 50);
	}
	flytime -= 1;

	MoveTo(GetX() + (flymethod - 1) * speed, GetY() - speed);
}

Alphatron::Alphatron(int x, int y, int hp, int damage, int speed, GameWorld *world) : Enemy(IMGID_ALPHATRON, x, y, hp, damage, 25, speed, world) {}

void Alphatron::Dead()
{
	if (IsDeath())
	{
		return;
	}
	m_world->IncreaseScore(50);
	m_world->Addobject(new Explosion(GetX(), GetY()));
	m_world->IncreaseDestroyed();
	SetDeath();
	m_world->DecreaseOnScreen();
}

void Alphatron::Attack()
{
	if ((m_world->GetDawnbreaker()->GetX() - GetX() <= 10) && (m_world->GetDawnbreaker()->GetX() - GetX() >= -10) && (m_energy >= 25))
	{
		if (randInt(1, 4) == 1)
		{
			m_energy -= 25;
			m_world->Addobject(new RedBullet(GetX(), GetY() - 50, attack, 180, m_world));
		}
	}
}

Sigmatron::Sigmatron(int x, int y, int hp, int speed, GameWorld *world) : Enemy(IMGID_SIGMATRON, x, y, hp, 0, 0, speed, world) {}

void Sigmatron::Dead()
{
	m_world->IncreaseScore(100);
	m_world->Addobject(new Explosion(GetX(), GetY()));
	m_world->IncreaseDestroyed();
	SetDeath();
	if (randInt(1, 5) == 1)
	{
		m_world->Addobject(new RestoreGoodie(GetX(), GetY(), m_world->GetDawnbreaker()));
	}
	m_world->DecreaseOnScreen();
}

void Sigmatron::Attack()
{
	if ((m_world->GetDawnbreaker()->GetX() - GetX() <= 10) && (m_world->GetDawnbreaker()->GetX() - GetX() >= -10))
	{
		flymethod = 1;
		flytime = WINDOW_HEIGHT;
		speed = 10;
	}
}

Omegatron::Omegatron(int x, int y, int hp, int damage, int speed, GameWorld *world) : Enemy(IMGID_OMEGATRON, x, y, hp, damage, 50, speed, world) {}

void Omegatron::Dead()
{
	m_world->IncreaseScore(200);
	m_world->Addobject(new Explosion(GetX(), GetY()));
	m_world->IncreaseDestroyed();
	SetDeath();
	if (randInt(1, 10) <= 4)
	{
		if (randInt(1, 10) <= 8)
		{
			m_world->Addobject(new PowerGoodie(GetX(), GetY(), m_world->GetDawnbreaker()));
		}
		else
		{
			m_world->Addobject(new MeteorGoodie(GetX(), GetY(), m_world->GetDawnbreaker()));
		}
	}
	m_world->DecreaseOnScreen();
}

void Omegatron::Attack()
{
	if (m_energy >= 50)
	{
		m_energy -= 50;
		m_world->Addobject(new RedBullet(GetX(), GetY() - 50, attack, 162, m_world));
		m_world->Addobject(new RedBullet(GetX(), GetY() - 50, attack, 198, m_world));
	}
}
