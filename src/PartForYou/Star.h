#pragma once
#include "GameObjects.h"

class Star : public GameObject
{
public:
    Star(int x,int y, double size);
    virtual void Update();
    void BeingHit(int damage) {}
};
