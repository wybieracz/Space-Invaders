/*@author Michal Pawlowski*/
/*@file Game.cpp*/

#include "Game.h"

Game::Game() {

	// creating all dynamic allocated elements

	menu = new Menu(textures.getTexture("start"), textures.getTexture("end"), textures.getFont());
	hud = new HUD(textures.getTexture("cannon"), textures.getFont());
	player = new Player(textures.getTexture("cannon"), textures.getTexture("destroyed_cannon"));
	ufo = new Ufo(textures.getTexture("ufo"), sounds.getSoundBuffer("ufo_lowpitch"));
	walls = new Walls(textures.getTexture("square1"), textures.getTexture("square2"), textures.getTexture("square3"), textures.getTexture("square4"), textures.getTexture("triangle1"), textures.getTexture("triangle2"), textures.getTexture("triangle3"), textures.getTexture("triangle4"));
	bullets = new PlayerBullets(sounds.getSoundBuffer("shoot"));
	enemies = new Enemies(textures.getTexture("octopus1"), textures.getTexture("octopus2"), textures.getTexture("crab1"), textures.getTexture("crab2"), textures.getTexture("squid1"), textures.getTexture("squid2"), textures.getTexture("enemy_bullet"));
	collision = new Collision(sounds.getSoundBuffer("explosion"));
}

Game::~Game() {

	// deleting all dynamic allocated elements

	delete menu;
	delete hud;
	delete player;
	delete ufo;
	delete walls;
	delete bullets;
	delete enemies;
	delete collision;
}

const bool Game::isWindowOpened() const {

	return utilities.isWindowOpened();		// checks is game window still opened
}

void Game::updateInput() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->isAttackPossible()) bullets->spawnBullet(player->getPosition().x); // creates new player bullet if conditions are true
}

void Game::newGame() {

	// reset all components for a new game

	result.resetLevel();
	result.resetScore();
	player->setNewCannon();
	bullets->deleteAllBullets();
	enemies->deleteAllEnemiesAndBullets();
	ufo->reset();
	walls->rebuiltWalls();
	startSounds();
	isGameEnded = false;
	isNewGameStarted = false;
}

void Game::updateStartMenu() {

	menu->scaleText(timer.getDeltaTime());		// menu text animation
}

void Game::updateGame() {

	updateInput();	// update keyboard input
	player->update(timer.getDeltaTime());	// update player state
	enemies->update(result.getLevel(), isGameEnded, *bullets, timer.getDeltaTime());	// update enemies state
	ufo->update(timer.getDeltaTime());	// update ufo state
	bullets->updateBullets(timer.getDeltaTime());	// update player bullets state
	collision->checkCollisions(result.getScore(), isGameEnded, *player, *ufo, bullets->getBulletsVector(), enemies->getBulletsVector(), enemies->getEnemyList(), *walls);	// checks all possible collisions
	hud->updateHUD(result.getScore(), result.getLevel());	// update HUD informations
}

void Game::updateEndMenu() {

	result.updateBestScore();	// save score if is the best
	menu->updateScore(result.getScore(), result.getBestScore());	// save score as menu text
	if (isNewGameStarted) newGame();	// create new game
}

void Game::renderGame() {

	// render all objects on screen

	player->render(utilities.getWindow());
	walls->renderWalls(utilities.getWindow());
	enemies->render(utilities.getWindow());
	ufo->render(utilities.getWindow());
	bullets->renderBullets(utilities.getWindow());
	hud->renderHUD(utilities.getWindow(), player->getHealth());

	if (isGameEnded) menu->endMenu(utilities.getWindow());
}

void Game::stopSounds() {

	// stop all sounds

	ufo->stopUfoSound();
	sounds.stopMusic();
	sounds.playGameOverSound();
	isMusicActive = false;
}

void Game::startSounds() {

	// start music

	sounds.stopGameOverSound();
	sounds.playMusic();
	isMusicActive = true;
}

void Game::update() {

	utilities.inputCheck(isGameStarted, isGameEnded, isNewGameStarted);
	
	if (!isGameStarted) updateStartMenu();	// update start menu
	else {

		if (!isGameEnded) updateGame();	// update game
		else {

			if (isMusicActive) stopSounds();
			updateEndMenu();	// update end menu
		}
	}

	timer.CalculateDeltaTime();	// calculate time of one cycle
}

void Game::render() {

	(*utilities.getWindow()).clear();

	if (!isGameStarted) menu->startMenu(utilities.getWindow());
	else renderGame();
	
	(*utilities.getWindow()).display();
}
