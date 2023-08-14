#include "GameWorld.h"
#include "Dawnbreaker.h"
#include "Star.h"
#include "Enemy.h"
#include "Bullet.h"

GameWorld::GameWorld() : m_heart(3), m_dawnbreaker(nullptr), onScreen(0), destroyed(0) {}

GameWorld::~GameWorld()
{
    CleanUp();
}

void GameWorld::Init()
{
    m_dawnbreaker = new Dawnbreaker(this);

    int x;
    int y;
    double size;
    GameObject *star;

    for (int i = 0; i < 30; i++)
    {
        x = randInt(0, WINDOW_WIDTH - 1);
        y = randInt(0, WINDOW_HEIGHT - 1);
        size = randInt(10, 40) / 100.0;
        star = new Star(x, y, size);
        m_gameObjects.push_back(star);
    }

    destroyed = 0;
    onScreen = 0;
}

LevelStatus GameWorld::Update()
{
    // new star
    if (randInt(0, 29) == 0)
    {
        m_gameObjects.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, randInt(10, 40) / 100.0));
    }
    // new enemy
    int todestroy = 3 * GetLevel() - destroyed;
    int maxOnScreen = (5 + GetLevel()) / 2;
    int allowed = todestroy <= maxOnScreen ? todestroy : maxOnScreen;
    if (randInt(1, 100) <= (allowed - onScreen))
    {
        int P1 = 6;
        int P2 = GetLevel() - 1 > 0 ? 2 * GetLevel() - 2 : 0;
        int P3 = GetLevel() - 2 > 0 ? 3 * GetLevel() - 6 : 0;
        int temp = randInt(1, P1 + P2 + P3);
        if (temp <= P1)
        {
            Addobject(new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + 2 * GetLevel(), 4 + GetLevel(), 2 + GetLevel() / 5, this));
        }
        else if (temp <= P1 + P2)
        {
            Addobject(new Sigmatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 25 + 5 * GetLevel(), 2 + GetLevel() / 5, this));
        }
        else
        {
            Addobject(new Omegatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + GetLevel(), 2 + 2 * GetLevel(), 3 + GetLevel() / 4, this));
        }
        onScreen += 1;
    }
    // update everyone
    m_dawnbreaker->Update();
    for (auto i : m_gameObjects)
    {
        i->Update();
    }
    // test failure
    if (m_dawnbreaker->IsDeath())
    {
        m_heart -= 1;
        return LevelStatus::DAWNBREAKER_DESTROYED;
    }
    // test success
    if (destroyed >= 3 * GetLevel())
    {
        return LevelStatus::LEVEL_CLEARED;
    }
    // delete death
    for (auto i = m_gameObjects.begin(); i != m_gameObjects.end();)
    {
        auto object = *i;
        if (object->IsDeath())
        {
            delete object;
            m_gameObjects.erase(i++);
        }
        else
        {
            i++;
        }
    }
    m_dawnbreaker->SetBar(destroyed, GetScore());

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
    for (auto object : m_gameObjects)
    {
        delete object;
    }
    m_gameObjects.clear();
    delete m_dawnbreaker;
    m_dawnbreaker = nullptr;
}

bool GameWorld::IsGameOver() const
{
    if (m_heart <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameWorld::Addobject(GameObject *object)
{
    m_gameObjects.push_back(object);
}

bool GameWorld::HitEnemy(int damage, GameObject *bullet)
{
    for (auto object : m_gameObjects)
    {
        if (object->IsEnemy() && IsCollision(object, bullet) && !object->IsDeath() && !bullet->IsDeath())
        {
            object->BeingHit(damage);
            return true;
        }
    }
    return false;
}

bool GameWorld::HitDawn(int damage, GameObject *bullet)
{
    if (IsCollision(m_dawnbreaker, bullet) && !bullet->IsDeath() && !m_dawnbreaker->IsDeath())
    {
        m_dawnbreaker->BeingHit(damage);
        return true;
    }
    return false;
}

void GameWorld::EnemyBeHit(GameObject *enemy)
{
    for (auto object : m_gameObjects)
    {
        if ((object->IsMyBullet()) && IsCollision(object, enemy) && !object->IsDeath() && !enemy->IsDeath())
        {
            enemy->BeingHit(object->GetDamage());
            object->afterHit();
            if (enemy->IsDeath())
            {
                return;
            }
        }
    }
}

bool GameWorld::CollideDawn(GameObject *enemy)
{
    if (IsCollision(m_dawnbreaker, enemy) && !m_dawnbreaker->IsDeath() && !enemy->IsDeath())
    {
        m_dawnbreaker->BeingHit(20);
        return true;
    }
    else
    {
        return false;
    }
}

GameObject *GameWorld::GetDawnbreaker()
{
    return m_dawnbreaker;
}

void GameWorld::IncreaseDestroyed()
{
    destroyed += 1;
}

void GameWorld::DecreaseOnScreen()
{
    onScreen -= 1;
}