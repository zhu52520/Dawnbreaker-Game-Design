#pragma once
#include "GameObjects.h"
#include "utils.h"
class Explosion :
    public GameObject
{
public:
    Explosion(int x, int y);
    void Update();

private:
    int count;
};

