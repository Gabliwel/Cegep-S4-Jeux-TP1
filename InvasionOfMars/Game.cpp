#include "Game.h"
#include "ContentManager.h"
#include <cstdlib>  //Pour random     
#include <ctime>  //Pour random

Game::Game()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner

	renderWindow.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Invasion of Mars");  // , Style::Titlebar); / , Style::FullScreen);
	
	mainView = View(FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	mainView.setCenter(WORLD_WIDTH / 2, WORLD_HEIGHT / 2);
	
	hudView = View(FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	//mainWin.setVerticalSyncEnabled(true);
	renderWindow.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

int Game::run()
{
	srand(time(NULL));  //On se donne un seed random qui va nécessairement servir

	if (!init())return EXIT_FAILURE;

	while (renderWindow.isOpen())
	{
		getInputs();
		update();
		draw();
	}

	if (!unload())return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

bool Game::init()
{
	if (!ContentManager::getInstance().loadContent()) return false;
	if (!music.openFromFile("Ressources\\Sounds\\Music\\Carpenter_brut_remorse.ogg")) return false;
	backgroundSound.setBuffer(ContentManager::getInstance().getHordeBuffer());

	field.setTexture(ContentManager::getInstance().getBackgroundTexture());
	field.setPosition(0, 0);
	field.setColor(Color(193, 68, 14, 255)); //Couleur "Rouge sol de Mars"

	player.init();
	player.setPosition(WORLD_CENTER_X, WORLD_CENTER_Y);

	for (int i = 0; i < NBR_ALIENS; i++)
	{
		aliens[i].init();
	}

	for (int i = 0; i < NBR_BONUS; i++)
	{
		bonus[i].init();
	}

	for (int i = 0; i < NB_LOADED_POINT_TEXT; i++)
	{
		ptText[i].setFont(ContentManager::getInstance().getFont());
		ptText[i].setCharacterSize(10);
		ptText[i].setFillColor(Color::White);
		ptText[i].setString("");
		textTimer[i] = DISPLAY_TIME_PT_SEC * 60;
	}

	chronoForEnemySpawn = SPAWN_SEC_BETWEEN_ENEMY * 60;

	hud.hudInit();	

	player.activate();
	music.setLoop(true);
	music.play();
	backgroundSound.setLoop(true);
	backgroundSound.play();
	return true;
}

void Game::getInputs()
{
	inputs.reset();

	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
			renderWindow.close();
	}
	Vector2f playerDirection;
	if (Joystick::isConnected(0))
	{
		//le / 100 à la fin: on ramène le tout à une échelle de 0 à 1: plus simple
		if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7)
		{
			if (!inputs.isInPauseBuffer)
			{
				inputs.isInPauseBuffer = true;
				inputs.isInPause = !inputs.isInPause;
			}
		}
		else
		{
			inputs.isInPauseBuffer = false;
		}
		if (!inputs.isInPause)
		{
			inputs.moveHorizontal = inputs.eliminateVibration(Joystick::getAxisPosition(0, Joystick::Axis::X)) / 100.0f;
			inputs.moveVertical = inputs.eliminateVibration(Joystick::getAxisPosition(0, Joystick::Axis::Y)) / 100.0f;
			playerDirection.x = inputs.eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U));
			playerDirection.y = inputs.eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
			if (playerDirection.x == 0 && playerDirection.y == 0)
			{
				inputs.noAngle = true;
			}
			else
			{
				inputs.angle = atan2f(playerDirection.y, playerDirection.x);
			}
			if (inputs.eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z)) < 0) inputs.fireMask = true;
		}
		inputs.isGamepadActive = true;
	}
	else
	{
		//Notez que les diagonales ne sont pas gérées actuellement et que le déplacement
		//est plus rapide en diagonale.  À vous de trouver une solution pour corriger ça.
		//Vous avez le droit d'ajouter une méthode dans la struct inputs qui ferait cette 
		//correction, un peu comme eliminateVibration.
		//Notez que si moveHorizontal et moveVectical sont toutes deux pas à 0, alors on est
		//en diagonal

		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			if (!inputs.isInPauseBuffer)
			{
				inputs.isInPauseBuffer = true;
				inputs.isInPause = !inputs.isInPause;
			}
		}
		else
		{
			inputs.isInPauseBuffer = false;
		}
		if (!inputs.isInPause)
		{
			if (Keyboard::isKeyPressed(Keyboard::A)) inputs.moveHorizontal -= 1.0f;
			if (Keyboard::isKeyPressed(Keyboard::D)) inputs.moveHorizontal += 1.0f;
			if (Keyboard::isKeyPressed(Keyboard::W)) inputs.moveVertical -= 1.0f;
			if (Keyboard::isKeyPressed(Keyboard::S)) inputs.moveVertical += 1.0f;
			if (Mouse::isButtonPressed(Mouse::Left)) inputs.fireMask = true;
			inputs.eliminateDiagonalSpeed();
			playerDirection = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
			inputs.angle = atan2f((playerDirection.y - player.getPosition().y), (playerDirection.x - player.getPosition().x));
		}
	}
}

//Vous devrez centrer la vue sur le player: https://www.sfml-dev.org/tutorials/2.4/graphics-view-fr.php
void Game::update()
{
	//On peut déplacer la vue, mais on peut aussi lui la centrer sur une position précise, 
	//comme celle du joueur (avec la méthode setCenter).  Quand votre joueur va se déplacer 
	//vous devrez centrer la vue sur lui.
	if (nbLifes == 0)
	{
		hud.setBigMsg("Game Over!");
		return;
	}

	if (inputs.isInPause)
	{
		music.pause();
		backgroundSound.pause();
		hud.setBigMsg("Pause");
		return;
	}
	if (Music::Paused == music.getStatus())
	{
		music.play();
		backgroundSound.play();
	}
	hud.setBigMsg("");
	mainView.move(inputs.moveHorizontal * 5.0f, inputs.moveVertical * 5.0f);
	player.updateMoveAndBullet(inputs);
	for (int i = 0; i < NBR_BONUS; i++)
	{
		bonus[i].isTaken(player);
	}
	updateAliens();
	updateTexts();
	updateAlienSpawn();
	if (scoreWatcherForExtraLife >= SCORE_FOR_EXTRA_LIFE)
	{
		scoreWatcherForExtraLife = SCORE_FOR_EXTRA_LIFE - scoreWatcherForExtraLife;
		nbLifes++;
	}
	hud.hubUpdate(totalPt, nbLifes);
	mainView.setCenter(player.getPosition().x, player.getPosition().y);
	ajustCrossingWorldLimits();
}

void Game::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.setView(mainView);
	renderWindow.draw(field);

	for (int i = 0; i < NBR_BONUS; i++)
	{
		bonus[i].draw(renderWindow);
	}

	for (int i = 0; i < NBR_ALIENS; i++)
		aliens[i].draw(renderWindow);

	for (Text text : ptText)
		renderWindow.draw(text);

	player.drawPlayerAndBullets(renderWindow);
	
	renderWindow.setView(hudView);
	hud.draw(renderWindow);
	renderWindow.setView(mainView);

	renderWindow.display();
}

bool Game::unload()
{
	return true;
}

void Game::ajustCrossingWorldLimits()
{
	if (mainView.getCenter().x < WORLD_LIMIT_MIN_X)
		mainView.setCenter(WORLD_LIMIT_MIN_X, mainView.getCenter().y);
	else if (mainView.getCenter().x > WORLD_LIMIT_MAX_X)
		mainView.setCenter(WORLD_LIMIT_MAX_X, mainView.getCenter().y);

	if (mainView.getCenter().y < WORLD_LIMIT_MIN_Y)
		mainView.setCenter(mainView.getCenter().x, WORLD_LIMIT_MIN_Y);
	else if (mainView.getCenter().y > WORLD_LIMIT_MAX_Y)
		mainView.setCenter(mainView.getCenter().x, WORLD_LIMIT_MAX_Y);
}

void Game::updateAliens()
{
	for (int i = 0; i < NBR_ALIENS; i++)
	{
		if (aliens[i].isActive())
		{
			if (!player.isDead() && !player.isUnstoppable() && player.getCollisionCircle().checkCollision(aliens[i].getCollisionCircle()))
			{
				player.die();
				nbLifes--;
				lastPt = INITIAL_PT;
			}
			aliens[i].moveAlien(player.getPosition(), player.isDead());
			if (player.bulletTouched(aliens[i]) && !aliens[i].getIsSpawnState())
			{
				for (int j = 0; j < NB_LOADED_POINT_TEXT; j++)
				{
					if (ptText[j].getString() == "")
					{
						textTimer[j] = DISPLAY_TIME_PT_SEC * 60;
						if (lastPt == 0)
							lastPt = INITIAL_PT;
						else
							lastPt += ADDED_PT;
						scoreWatcherForExtraLife += lastPt;
						ptText[j].setPosition(player.getPositionOfLastKill());
						ptText[j].setString(std::to_string(lastPt));
						totalPt += lastPt;
						break;
					}
				}
				int result = rand() % MAX_PERCENTAGE + MIN_PERCENTAGE;
				if (result <= BONUS_PERCENTAGE)
				{
					for (int k = 0; k < NBR_BONUS; k++)
					{
						if (!bonus[k].isActive())
						{
							bonus[k].spawn(aliens[i].getPosition());
							break;
						}
					}
				}
				aliens[i].die();
			}
			
		}
	}
}

void Game::updateTexts()
{
	for (int i = 0; i < NB_LOADED_POINT_TEXT; i++)
	{
		if (ptText[i].getString() != "")
		{
			if (textTimer[i] <= 0)
			{
				ptText[i].setString("");
				textTimer[i] = DISPLAY_TIME_PT_SEC * 60;
			}
			else
			{
				textTimer[i]--;
			}
		}
	}
}

void Game::updateAlienSpawn()
{
	if (!player.isDead())
	{
		chronoForEnemySpawn--;
	}
	if (chronoForEnemySpawn <= 0)
	{
		for (int i = 0; i < NBR_ALIENS; i++)
		{
			if (!aliens[i].isActive())
			{
				aliens[i].spawn(player);
				chronoForEnemySpawn = SPAWN_SEC_BETWEEN_ENEMY * 60;
				break;
			}
		}
	}
}
