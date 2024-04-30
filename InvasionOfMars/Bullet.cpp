#include "Bullet.h"
#include "Constants.h"

const float Bullet::BULLET_SPEED = 20.0f;

Bullet::Bullet()
{
	bulletMove.x = bulletMove.y = 0.0f;
	lifeTime = 0;
	deactivate();
}

void Bullet::setBulletSoundBuffer(const SoundBuffer& soundBuffer)
{
	bulletSound.setBuffer(soundBuffer);
}

void Bullet::fire(const GameObject& origin)
{
	setPosition(origin.getPosition());
	bulletMove.x = BULLET_SPEED * cos(origin.getRotationRadians());
	bulletMove.y = BULLET_SPEED * sin(origin.getRotationRadians());

	lifeTime = MAX_LIFETIME;

	bulletSound.play();
	activate();
}

void Bullet::fly()
{
	if (!isActive()) return;

	move(bulletMove);

	if (getPosition().x > WORLD_WIDTH - getTexture()->getSize().x / 2)
	{
		deactivate();
	}
	else if (getPosition().x < getTexture()->getSize().x / 2)
	{
		deactivate();
	}
	if (getPosition().y > WORLD_HEIGHT - getTexture()->getSize().y / 2)
	{
		deactivate();
	}
	else if (getPosition().y < getTexture()->getSize().y / 2)
	{
		deactivate();
	}
}
