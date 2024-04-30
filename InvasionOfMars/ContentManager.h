#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class ContentManager
{
public:
	bool loadContent();
	const Texture& getBackgroundTexture() const;
	const Texture& getPlayerTexture() const;
	const Texture& getLogoTexture() const;
	const Texture& getProjectileTexture(const int projectileNumber) const;
	const Texture& getAlienTexture(const int alienTextureNumber) const;

	const SoundBuffer& ContentManager::getHordeBuffer() const;
	const SoundBuffer& ContentManager::getAlienDeathBuffer() const;
	const SoundBuffer& ContentManager::getPlayerDeathBuffer() const;
	const SoundBuffer& ContentManager::getPreciseShotBuffer(const int bufferNumber) const;
	const SoundBuffer& ContentManager::getTokenSoundBuffer() const;
	const SoundBuffer& ContentManager::getExplosionSoundBuffer() const;

	const Font& getFont() const;

	static ContentManager& getInstance();

	static const int ALIEN_TEXTURE_NUMBER = 3;
	static const int PROJECTILE_TEXTURE_NUMBER = 2;
	static const int PROJECTILE_BUFFER_NUMBER = 2;

private:
	ContentManager() {}
	ContentManager(ContentManager& other) {}
	void operator=(const ContentManager&) {}
	static ContentManager instance;

	Texture backgroundTexture;
	Texture playerTexture;
	Texture alienTexture[ALIEN_TEXTURE_NUMBER];
	Texture projectileTexture[PROJECTILE_TEXTURE_NUMBER];
	Texture logoTexture;

	SoundBuffer projectileBuffer[PROJECTILE_BUFFER_NUMBER];
	SoundBuffer hordeBuffer;
	SoundBuffer alienDeathBuffer;
	SoundBuffer playerDeathBuffer;
	SoundBuffer tokenSoundBuffer;
	SoundBuffer explosionSoundBuffer;

	Font font;
};