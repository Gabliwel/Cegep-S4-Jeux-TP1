#include "Alien.h"
#include "ContentManager.h"
#include "Constants.h"

Alien::Alien()
{
}

void Alien::init()
{
	setTexture(ContentManager::getInstance().getAlienTexture(rand() % (ContentManager::getInstance().ALIEN_TEXTURE_NUMBER -1) + 0));
	setOrigin(getTexture()->getSize().x / 2, getTexture()->getSize().y / 2);
	deathSound.setBuffer(ContentManager::getInstance().getAlienDeathBuffer());
}

void Alien::spawn(Player player)
{
	isSpawnState = true;
	int xMinPlayer = player.getPosition().x - player.SAFE_ZONE;
	int xMaxPlayer = player.getPosition().x + player.SAFE_ZONE;
	int xMin = getTexture()->getSize().x / 2;
	int xMax = WORLD_WIDTH - (getTexture()->getSize().x /2);
	int yMinPlayer = player.getPosition().y - player.SAFE_ZONE;
	int yMaxPlayer = player.getPosition().y + player.SAFE_ZONE;
	int yMin = getTexture()->getSize().y / 2;
	int yMax = WORLD_HEIGHT - (getTexture()->getSize().y / 2);
	int randX = getRandomCoords(xMinPlayer, xMaxPlayer, xMin, xMax);
	int randY = getRandomCoords(yMinPlayer, yMaxPlayer, yMin, yMax);

	setPosition(sf::Vector2f(randX, randY));
	setScale(Vector2f(ALIEN_DEFAULT_SCALE, ALIEN_DEFAULT_SCALE));
	activate();
}

void Alien::moveAlien(Vector2f playerPosition, bool goOpposite)
{
	if (!isActive()) return;
	if (!isSpawnState)
	{
		float angle = atan2f((playerPosition.y - getPosition().y), (playerPosition.x - getPosition().x));
		if (goOpposite)
			angle += M_PI;
		setRotation(angle * (180 / M_PI));
		sf::Vector2f offset;

		offset.x = cos(angle) * ALIEN_SPEED;
		offset.y = sin(angle) * ALIEN_SPEED;

		move(offset);
	}
	else
	{
		setScale(getScale().x+0.01, getScale().y + 0.01);
		if (getScale().x >= 1)
		{
			isSpawnState = false;
		}
	}
}

bool Alien::getIsSpawnState()
{
	return isSpawnState;
}

int Alien::getRandomCoords(int minPlayer, int maxPlayer, int min, int max)
{
	int randomValue;
	if (minPlayer <= min)
	{
		randomValue = (rand() % max + maxPlayer);
	}
	else if (maxPlayer >= max)
	{
		randomValue = (rand() % minPlayer + min);
	}
	else
	{
		if ((rand() % 2 + 1) == 1)
		{
			randomValue = (rand() % max + maxPlayer);
		}
		else
		{
			randomValue = (rand() % minPlayer + min);
		}
	}
	return randomValue;
}

void Alien::die()
{
	deactivate();
	deathSound.play();
}
