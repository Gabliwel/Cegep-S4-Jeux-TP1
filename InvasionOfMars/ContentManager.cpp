#include "ContentManager.h"

ContentManager ContentManager::instance;

ContentManager& ContentManager::getInstance()
{
	return instance;
}

bool ContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Ressources\\Sprites\\Backgrounds\\MoonReflectiveBackground.png")) return false;
	
	if (!playerTexture.loadFromFile("Ressources\\Sprites\\SpacemanAndAliens\\Spaceman.png")) return false;

	if (!alienTexture[0].loadFromFile("Ressources\\Sprites\\SpacemanAndAliens\\Alien1.png")) return false;
	if (!alienTexture[1].loadFromFile("Ressources\\Sprites\\SpacemanAndAliens\\Alien2.png")) return false;
	if (!alienTexture[2].loadFromFile("Ressources\\Sprites\\SpacemanAndAliens\\Alien3.png")) return false;

	if (!logoTexture.loadFromFile("Ressources\\Sprites\\Logos\\BoostLogo.png")) return false;

	if (!projectileTexture[0].loadFromFile("Ressources\\Sprites\\Projectiles\\Blast.png")) return false;
	if (!projectileTexture[1].loadFromFile("Ressources\\Sprites\\Projectiles\\Bullet.png")) return false;

	if (!hordeBuffer.loadFromFile("Ressources\\Sounds\\Characters\\Horde.ogg")) return false;
	if (!alienDeathBuffer.loadFromFile("Ressources\\Sounds\\Characters\\AlienDeath.ogg")) return false;
	if (!playerDeathBuffer.loadFromFile("Ressources\\Sounds\\Characters\\PlayerDeath.ogg")) return false;
	if (!projectileBuffer[0].loadFromFile("Ressources\\Sounds\\SpaceShots\\Shot01.ogg")) return false;
	if (!projectileBuffer[1].loadFromFile("Ressources\\Sounds\\SpaceShots\\Shot02.ogg")) return false;
	if (!tokenSoundBuffer.loadFromFile("Ressources\\Sounds\\SpaceShots\\ToggleSound.ogg")) return false;
	if (!explosionSoundBuffer.loadFromFile("Ressources\\Sounds\\SpaceShots\\Explosion.ogg")) return false;

	if (!font.loadFromFile("Ressources\\Fonts\\segoepr.ttf")) return false;

	return true;
}

const Texture& ContentManager::getBackgroundTexture() const { return backgroundTexture; }
const Texture& ContentManager::getPlayerTexture() const { return playerTexture; }
const Texture& ContentManager::getLogoTexture() const { return logoTexture; }
const Texture& ContentManager::getProjectileTexture(const int projectileNumber) const { return projectileTexture[projectileNumber]; }
const Texture& ContentManager::getAlienTexture(const int alienTextureNumber) const { return alienTexture[alienTextureNumber]; }

const SoundBuffer& ContentManager::getHordeBuffer() const { return hordeBuffer; }
const SoundBuffer& ContentManager::getAlienDeathBuffer() const { return alienDeathBuffer; }
const SoundBuffer& ContentManager::getPlayerDeathBuffer() const { return playerDeathBuffer; }
const SoundBuffer& ContentManager::getPreciseShotBuffer(const int bufferNumber) const
{
	return projectileBuffer[bufferNumber];
}
const SoundBuffer& ContentManager::getTokenSoundBuffer() const { return tokenSoundBuffer; }
const SoundBuffer& ContentManager::getExplosionSoundBuffer() const { return explosionSoundBuffer; }

const Font& ContentManager::getFont() const { return font; }
