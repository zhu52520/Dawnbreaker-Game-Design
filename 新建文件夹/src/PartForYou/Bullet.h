#pragma once
#include "GameObjects.h"
#include "GameWorld.h"

class Bullet :
    public GameObject
{
public:
    Bullet(int imageID,int x,int y,double size,int damage,int direction, GameWorld* world);
    virtual void Update();
    virtual void afterHit() {};
    virtual void move() = 0;
    void BeingHit(int damage) {}
    GameWorld* GetWorld();
    int GetDamage();

private:
    GameWorld* m_world;
    int m_damage;
};

class BlueBullet :
    public Bullet
{
public:
    BlueBullet(int x, int y, double size, int damage, GameWorld* world);
    void afterHit();
    void move();

};

class Meteor :
    public Bullet
{
public:
    Meteor(int x, int y,GameWorld* world);
    void afterHit();
    void move();
};


class RedBullet :
    public Bullet
{
public:
    RedBullet(int x, int y, int damage,int direction, GameWorld* world);
    void Update();
    void afterHit();
    void move();
};