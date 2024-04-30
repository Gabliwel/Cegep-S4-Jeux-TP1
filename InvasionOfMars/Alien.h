#pragma once
#include "GameObject.h"
#include "Limits.h"
#include "Player.h"

class Alien : public GameObject
{
public:
	Alien();
	void init();
	void die();
	void spawn(Player player);
	void moveAlien(Vector2f playerPosition, bool goOpposite);
	bool getIsSpawnState();
private:
	const float ALIEN_SPEED = 5.0f;
	const float ALIEN_DEFAULT_SCALE = 0.40f;

	Sound deathSound;

	bool isSpawnState = false;

	int getRandomCoords(int minPlayer, int maxPlayer, int min, int max);
};

