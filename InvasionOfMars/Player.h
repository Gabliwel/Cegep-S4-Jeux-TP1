#pragma once
#include "GameObject.h"
#include "Inputs.h"
#include "Gun.h"

class Player : public GameObject
{
public:
	Player();
	void init();
	void movePlayer(Inputs inputs);
	void rotatePlayer(Inputs inputs);
	void die();
	bool isDead();
	bool isUnstoppable();
	bool isPowerMode();
	void updateDeadState();
	void updateMoveAndBullet(Inputs inputs);
	void drawPlayerAndBullets(RenderWindow& renderWindow);
	bool bulletTouched(const GameObject& alien);
	void powerUp();
	Vector2f getPositionOfLastKill();
	int SAFE_ZONE = 200;

private:
	const float PLAYER_SPEED = 10.f;
	const float PLAYER_COLLISION_RADIUS = 40.0f;

	static const int DEAD_STATE_SEC_TIME = 3;
	int deadStateChrono = 0;

	Sound dyingSound;

	static const int POWERED_STATE_SEC_TIME = 4;
	int poweredTimer = 0;

	static const int TRANSPARANCE_STATE_SEC_TIME = 3;
	int transparanceTimer = 0;

	Gun defaultGun;
	Gun poweredGun;

	Vector2f positionOfLastKill;
};

