#include "Hud.h"
#include "ContentManager.h"
#include "Constants.h"

Hud::Hud()
{
}

void Hud::hudInit()
{
	bigMsg.setFont(ContentManager::getInstance().getFont());
	bigMsg.setString("Aliens are invading Mars!!!");
	bigMsg.setCharacterSize(50);
	bigMsg.setFillColor(Color::Red);
	bigMsg.setOrigin(bigMsg.getLocalBounds().width / 2, bigMsg.getLocalBounds().height / 2);
	bigMsg.setPosition(SCREEN_WIDTH /2, 300.0f);

	points.setFont(ContentManager::getInstance().getFont());
	points.setCharacterSize(20);
	points.setFillColor(Color::White);
	points.setPosition(10.0f, 10.0f);

	lives.setFont(ContentManager::getInstance().getFont());
	lives.setCharacterSize(20);
	lives.setFillColor(Color::White);
	lives.setPosition(10.0f, 50.0f);
}

void Hud::hubUpdate(int currentPoints, int currentLives)
{
	points.setString("Points: "+std::to_string(currentPoints));
	lives.setString("Lives: " + std::to_string(currentLives));
}


void Hud::draw(RenderWindow& renderWindow)
{
	renderWindow.draw(bigMsg);
	renderWindow.draw(points);
	renderWindow.draw(lives);
}

void Hud::setBigMsg(String msg)
{
	bigMsg.setString(msg);
	bigMsg.setOrigin(bigMsg.getLocalBounds().width / 2, bigMsg.getLocalBounds().height / 2);
	bigMsg.setPosition(SCREEN_WIDTH / 2, 300.0f);
}
