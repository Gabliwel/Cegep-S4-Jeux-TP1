#pragma once
#include "Bullet.h"

class Gun
{
public:
	Gun();
	void init(int bulletNb, int soundNb, bool gunHasCollision, int givenMaxRecoil);
	void fire(const GameObject& player);
	void updateBullet();
	void drawBullets(RenderWindow& renderWindow);
	bool bulletTouched(const GameObject& alien);
	Vector2f getPositionOfLastKill();
	int updateAndCheckRecoil();

private:
	static const int NBR_BULLETS = 25;
	Bullet bullets[NBR_BULLETS];
	int recoil = 0;
	int maxRecoil = 15;

	Vector2f positionOfLastKill;
	bool hasCollision;
};