#pragma once
#include "GameObjects.h"
#include "Dawnbreaker.h"

class Goodie :
    public GameObject
{
public:
    Goodie(int imageID, int x, int y, GameObject* dawnbreaker);
    void Update();
    virtual void collided()=0;
    GameObject*  m_dawnbreaker;
};

class RestoreGoodie :
    public Goodie
{
public:
    RestoreGoodie(int x, int y, GameObject* dawnbreaker);
    void collided();
};

class PowerGoodie :
    public Goodie
{
public:
    PowerGoodie(int x, int y, GameObject* dawnbreaker);
    void collided();
};

class MeteorGoodie :
    public Goodie
{
public:
    MeteorGoodie(int x, int y, GameObject* dawnbreaker);
    void collided();
};
