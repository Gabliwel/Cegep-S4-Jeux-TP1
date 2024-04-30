#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
public:
	Hud();
	void hudInit();
	void hubUpdate(int currentPoints, int currentLives);
	void draw(RenderWindow& renderWindow);
	void setBigMsg(String msg);

private:
	Text bigMsg;
	Text points;
	Text lives;
};

