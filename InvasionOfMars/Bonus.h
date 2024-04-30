#pragma once
#include "GameObject.h"
#include "Player.h"

class Bonus : public GameObject
{
public:
	Bonus();
	void init();
	void isTaken(Player& player);
	void spawn(Vector2f position);
private:
	Sound bonusSound;
};