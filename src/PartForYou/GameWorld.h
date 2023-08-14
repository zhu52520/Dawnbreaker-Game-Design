#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"
#include "GameObjects.h"



class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void Addobject(GameObject* object);

  bool HitEnemy(int damage, GameObject* bullet);

  bool HitDawn(int damage, GameObject* bullet);

  void EnemyBeHit(GameObject* enemy);

  bool CollideDawn(GameObject* enemy);

  GameObject* GetDawnbreaker();

  void IncreaseDestroyed();

  void DecreaseOnScreen();

  int GetHeart() { return m_heart; }

private:
  std::list<GameObject*> m_gameObjects;
  GameObject *m_dawnbreaker;
  int m_heart;
  int destroyed;
  int onScreen;

};

#endif // !GAMEWORLD_H__
