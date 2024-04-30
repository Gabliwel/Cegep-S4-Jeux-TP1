#include "Gun.h"
#include "ContentManager.h"
#include "Constants.h"

Gun::Gun()
{

}

void Gun::init(int bulletNb, int soundNb, bool gunHasCollision, int givenMaxRecoil)
{
	for (int i = 0; i < NBR_BULLETS; i++)
	{
		bullets[i].initialize(ContentManager::getInstance().getProjectileTexture(bulletNb), Vector2f(-1000.0f, -1000.0f), WORLD_WIDTH, WORLD_HEIGHT);
		bullets[i].setBulletSoundBuffer(ContentManager::getInstance().getPreciseShotBuffer(soundNb));
	}
	hasCollision = gunHasCollision;
	maxRecoil = givenMaxRecoil;
}

void Gun::fire(const GameObject& player)
{
	for (int i = 0; i < NBR_BULLETS; i++)
	{
		if (!bullets[i].isActive())
		{
			bullets[i].fire(player);
			recoil = maxRecoil;
			break;
		}
	}
}

void Gun::updateBullet()
{
	for (int i = 0; i < NBR_BULLETS; i++)
		bullets[i].fly();
}

void Gun::drawBullets(RenderWindow& renderWindow)
{
	for (int i = 0; i < NBR_BULLETS; i++)
		bullets[i].draw(renderWindow);
}

bool Gun::bulletTouched(const GameObject& alien)
{
	for (int j = 0; j < NBR_BULLETS; j++)
	{
		if (bullets[j].isActive() && alien.getGlobalBounds().intersects(bullets[j].getGlobalBounds()))
		{
			positionOfLastKill = bullets[j].getPosition();
			if(hasCollision) bullets[j].deactivate();
			return true;
		}
	}
	return false;
}

Vector2f Gun::getPositionOfLastKill()
{
	return positionOfLastKill;
}

int Gun::updateAndCheckRecoil()
{
	recoil--;
	return recoil;
}
