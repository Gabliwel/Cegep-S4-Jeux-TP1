#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Inputs.h"
#include "Player.h"
#include "Alien.h"
#include "Hud.h"
#include "Bullet.h"
#include "Bonus.h"

using namespace sf;

class Game
{
public:
	Game();
	int run();

private:
	const int WORLD_CENTER_X = WORLD_WIDTH / 2;
	const int WORLD_CENTER_Y = WORLD_HEIGHT / 2;

	//Puisque la utilise des positions centrales, les limites d'affichage
	//sont les positions centrales des cadres limites.
	const int WORLD_LIMIT_MIN_X = SCREEN_WIDTH / 2;
	const int WORLD_LIMIT_MIN_Y = SCREEN_HEIGHT / 2;
	const int WORLD_LIMIT_MAX_X = WORLD_WIDTH - WORLD_LIMIT_MIN_X;
	const int WORLD_LIMIT_MAX_Y = WORLD_HEIGHT - WORLD_LIMIT_MIN_Y;

	Inputs inputs;
	Hud hud;

	Music music;
	Sound backgroundSound;

	Sprite field;
	Player player;

	static const int NBR_ALIENS = 50;
	Alien aliens[NBR_ALIENS];

	static const int NBR_BONUS = 20;
	Bonus bonus[NBR_BONUS];

	int chronoForEnemySpawn;
	float SPAWN_SEC_BETWEEN_ENEMY = 0.4f;

	static const int NB_LOADED_POINT_TEXT = NBR_ALIENS + 5;
	Text ptText[NB_LOADED_POINT_TEXT];
	int textTimer[NB_LOADED_POINT_TEXT];
	static const int DISPLAY_TIME_PT_SEC = 1;

	static const int INITIAL_PT = 100;
	static const int ADDED_PT = 10;
	int lastPt = 0;
	int totalPt = 0;
	int scoreWatcherForExtraLife = 0;

	int nbLifes = 5;
	static const int SCORE_FOR_EXTRA_LIFE = 15000;

	static const int BONUS_PERCENTAGE = 5;
	static const int MIN_PERCENTAGE = 0;
	static const int MAX_PERCENTAGE = 100;

	bool init();
	void getInputs();
	void update();
	void draw();
	bool unload();
	void ajustCrossingWorldLimits();
	void updateAliens();
	void updateTexts();
	void updateAlienSpawn();

	RenderWindow renderWindow;
	View mainView;
	View hudView;
	Event event;
};