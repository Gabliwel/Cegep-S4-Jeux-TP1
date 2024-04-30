#include "Player.h"
#include "ContentManager.h"
#include "Constants.h"

Player::Player()
{

}

void Player::init()
{
	setTexture(ContentManager::getInstance().getPlayerTexture());
	setOrigin(getTexture()->getSize().x / 2.f, getTexture()->getSize().y / 2.f);
	setCollisionRadius(PLAYER_COLLISION_RADIUS);
	defaultGun.init(1, 1, true, 15);
	poweredGun.init(0, 0, false, 20);
	dyingSound.setBuffer(ContentManager::getInstance().getPlayerDeathBuffer());
}

void Player::movePlayer(Inputs inputs)
{
	move(inputs.moveHorizontal * PLAYER_SPEED, inputs.moveVertical * PLAYER_SPEED);
	if (getPosition().x > WORLD_WIDTH - getTexture()->getSize().x / 2)
	{
		setPosition(WORLD_WIDTH - (getTexture()->getSize().x / 2.f), getPosition().y);
	}
	else if (getPosition().x < getTexture()->getSize().x / 2.f)
	{
		setPosition(getTexture()->getSize().x / 2.f, getPosition().y);
	}
	if (getPosition().y > WORLD_HEIGHT - (getTexture()->getSize().y / 2.f))
	{
		setPosition(getPosition().x, WORLD_HEIGHT - (getTexture()->getSize().y / 2.f));
	}
	else if (getPosition().y < getTexture()->getSize().y / 2.f)
	{
		setPosition(getPosition().x, getTexture()->getSize().y / 2.f);
	}
	rotatePlayer(inputs);
	if (transparanceTimer != 0)
	{
		transparanceTimer--;
	}
	else if (poweredTimer != 0)
	{
		poweredTimer--;
	}
	else
	{
		setColor(sf::Color(255, 255, 255, 255));
	}
}

void Player::rotatePlayer(Inputs inputs)
{
	if (!inputs.noAngle)
	{
		setRotation(inputs.angle * RADIANS_TO_DEGREE);
		setRotationRadians(inputs.angle);
	}
}

void Player::die()
{
	deadStateChrono = DEAD_STATE_SEC_TIME * 60;
	poweredTimer = 0;
	deactivate();
	dyingSound.play();
}

bool Player::isDead()
{
	return deadStateChrono != 0;
}

bool Player::isUnstoppable()
{
	return transparanceTimer != 0;
}

bool Player::isPowerMode()
{
	return poweredTimer != 0;
}

void Player::updateDeadState()
{
	deadStateChrono--;
	if (!isDead())
	{
		transparanceTimer = TRANSPARANCE_STATE_SEC_TIME * 60;
		activate();
		setColor(sf::Color(255, 255, 255, 128));
	}
}

void Player::updateMoveAndBullet(Inputs inputs)
{
	if (!isDead())
	{
		movePlayer(inputs);
		if (!isPowerMode())
		{
			if (defaultGun.updateAndCheckRecoil() <= 0 && inputs.fireMask) defaultGun.fire(*this);
		}
		else 
		{
			if (poweredGun.updateAndCheckRecoil() <= 0 && inputs.fireMask) poweredGun.fire(*this);
		}
	}
	else
	{
		updateDeadState();
	}
	defaultGun.updateBullet();
	poweredGun.updateBullet();
}

void Player::drawPlayerAndBullets(RenderWindow& renderWindow)
{
	defaultGun.drawBullets(renderWindow);
	poweredGun.drawBullets(renderWindow);
	draw(renderWindow);
}

bool Player::bulletTouched(const GameObject& alien)
{
	if (defaultGun.bulletTouched(alien))
	{
		positionOfLastKill = defaultGun.getPositionOfLastKill();
		return true;
	}
	else if (poweredGun.bulletTouched(alien))
	{
		positionOfLastKill = poweredGun.getPositionOfLastKill();
		return true;
	}
	return false;
}

void Player::powerUp()
{
	poweredTimer = POWERED_STATE_SEC_TIME * 60;
	setColor(sf::Color::Yellow);
}

Vector2f Player::getPositionOfLastKill()
{
	return positionOfLastKill;
}


