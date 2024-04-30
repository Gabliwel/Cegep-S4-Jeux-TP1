#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	void setBulletSoundBuffer(const SoundBuffer& soundBuffer);
	void fire(const GameObject& origin);
	void fly();

private:
	static const int MAX_LIFETIME = 120;
	static const float BULLET_SPEED;
	Vector2f bulletMove;
	Sound bulletSound;
	int lifeTime;
};
