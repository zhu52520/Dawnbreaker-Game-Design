#include "GameObjects.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size):
	ObjectBase(imageID,x,y,direction,layer,size),m_death(false),is_enemy(false),is_mybullet(false),is_enemybullet(false) {}

bool GameObject::IsDeath()
{
	return m_death;
}

void GameObject::SetDeath()
{
	m_death = true;
}

bool GameObject::IsEnemy()
{
	return is_enemy;
}

void GameObject::SetEnemy()
{
	is_enemy = true;
}

bool GameObject::IsMyBullet()
{
	return is_mybullet;
}

void GameObject::SetMyBullet()
{
	is_mybullet = true;
}

bool GameObject::IsEnemyBullet()
{
	return is_enemybullet;
}

void GameObject::SetEnemyBullet()
{
	is_enemybullet = true;
}