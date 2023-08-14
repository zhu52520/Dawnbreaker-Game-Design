#pragma once

#include "GameObjects.h"
#include "utils.h"
#include "GameWorld.h"

class Dawnbreaker:public GameObject
{
public:
    Dawnbreaker(GameWorld *world);
    void Update();
    void restore(int hp);
    void powerup(int power);
    void meteorup(int meteor);
    void BeingHit(int damage);
    int GetHealth() { return m_health; }
    void SetBar(int destroyed, int score);

private:
    GameWorld *m_world;
    int m_health;
    int m_energy;
    int m_level;
    int m_meteor;
}; 

