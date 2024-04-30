#include "Bonus.h"
#include "ContentManager.h"

Bonus::Bonus()
{
}

void Bonus::init()
{
	setTexture(ContentManager::getInstance().getLogoTexture());
	bonusSound.setBuffer(ContentManager::getInstance().getTokenSoundBuffer());
}

void Bonus::isTaken(Player& player)
{
	if (isActive())
	{
		if (getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			deactivate();
			player.powerUp();
			bonusSound.play();
		}
	}
}

void Bonus::spawn(Vector2f position)
{
	setPosition(position);
	activate();
}
