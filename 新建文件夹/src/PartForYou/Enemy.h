#pragma once
#include "GameObjects.h"
#include "GameWorld.h"
#include "Explosion.h"

class Enemy :
    public GameObject
{
public:
    Enemy(int imageID, int x, int y, int health, int damage, int energy,int speed, GameWorld* world);
    virtual void Update();
    void BeingHit(int damage);
    virtual void Dead()=0;
    virtual void Attack() {}
    void Move();

    int m_health;
    int energy_max;
    int m_energy;
    int attack;
    int speed;
    GameWorld* m_world;
    int flytime;
    int flymethod;
};

class Alphatron :
    public Enemy
{
public:
    Alphatron(int x, int y, int hp, int damage, int speed,GameWorld* world);
    void Dead();
    void Attack();
};

class Sigmatron :
    public Enemy
{
public:
    Sigmatron(int x, int y, int hp, int speed,GameWorld* world);
    void Dead();
    void Attack();
};

class Omegatron :
    public Enemy
{
public:
    Omegatron(int x, int y, int hp, int damage, int speed,GameWorld* world);
    void Dead();
    void Attack();
};

