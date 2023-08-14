#include "Dawnbreaker.h"
#include "Bullet.h"

Dawnbreaker::Dawnbreaker(GameWorld *world) : GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0),
											 m_world(world), m_health(100), m_energy(10), m_level(0), m_meteor(0) {}

void Dawnbreaker::Update()
{
	if (!IsDeath())
	{
		if ((m_world->GetKey(KeyCode::UP)) && (GetY() <= WINDOW_HEIGHT - 1 - 4))
		{
			MoveTo(GetX(), GetY() + 4);
		}
		if ((m_world->GetKey(KeyCode::DOWN)) && (GetY() >= 54))
		{
			MoveTo(GetX(), GetY() - 4);
		}
		if ((m_world->GetKey(KeyCode::RIGHT)) && (GetX() <= WINDOW_WIDTH - 1 - 4))
		{
			MoveTo(GetX() + 4, GetY());
		}
		if ((m_world->GetKey(KeyCode::LEFT)) && (GetX() >= 4))
		{
			MoveTo(GetX() - 4, GetY());
		}

		if (m_world->GetKey(KeyCode::FIRE1))
		{
			if (m_energy >= 10)
			{
				m_energy -= 10;
				m_world->Addobject(new BlueBullet(GetX(), GetY() + 50, 0.5 + 0.1 * m_level, 5 + 3 * m_level, m_world));
			}
		}

		if (m_world->GetKeyDown(KeyCode::FIRE2))
		{
			if (m_meteor >= 1)
			{
				m_meteor -= 1;
				m_world->Addobject(new Meteor(GetX(), GetY() + 100, m_world));
			}
		}
		if (m_energy < 10)
		{
			m_energy += 1;
		}
	}
}

void Dawnbreaker::restore(int hp)
{
	m_health += hp;
	if (m_health > 100)
	{
		m_health = 100;
	}
	m_world->IncreaseScore(20);
}

void Dawnbreaker::powerup(int power)
{
	m_level += 1;
	m_world->IncreaseScore(20);
}

void Dawnbreaker::meteorup(int meteor)
{
	m_meteor += 1;
	m_world->IncreaseScore(20);
}

void Dawnbreaker::BeingHit(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		SetDeath();
	}
}

void Dawnbreaker::SetBar(int destroyed, int score)
{
	std::string temp = "HP: ";
	temp += std::to_string(m_health) + "/100   Meteors: " + std::to_string(m_meteor) + "   Lives: " + std::to_string(m_world->GetHeart()) + "   Level: " + std::to_string(m_world->GetLevel()) + "   Enemies: " + std::to_string(destroyed) + "/" + std::to_string(3 * m_world->GetLevel()) + "   Score: " + std::to_string(score);
	m_world->SetStatusBarMessage(temp);
}