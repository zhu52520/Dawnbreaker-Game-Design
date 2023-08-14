#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameObject : public ObjectBase {
    public:
    GameObject(int imageID, int x, int y, int direction, int layer, double size);
    virtual void Update() = 0;
    virtual void BeingHit(int damage) {}
    virtual int GetDamage() { return 0; }
    virtual void afterHit(){}
    virtual void restore(int hp){}
    virtual void powerup(int level) {}
    virtual void meteorup(int m) {}
    virtual int GetHealth() { return 0; }
    virtual void SetBar(int destroyed, int score) {}


    bool IsDeath();
    void SetDeath();
    bool IsEnemy();
    void SetEnemy();

    bool IsMyBullet();
    void SetMyBullet();
    bool IsEnemyBullet();
    void SetEnemyBullet();

private:
    bool m_death;
    bool is_enemy;
    bool is_mybullet;
    bool is_enemybullet;
};

inline bool IsCollision(GameObject* lhs, GameObject* rhs)
{
    double d2 = (lhs->GetX() - rhs->GetX()) * (lhs->GetX() - rhs->GetX()) + (lhs->GetY() - rhs->GetY()) * (lhs->GetY() - rhs->GetY());
    if (d2 < 30.0*30.0*(lhs->GetSize()+rhs->GetSize())* (lhs->GetSize() + rhs->GetSize()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif // GAMEOBJECTS_H__