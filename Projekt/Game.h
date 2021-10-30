#pragma once

/*@author Michal Pawlowski*/
/*@file Game.h*/

#include <iostream>
#include "SfmlUtilities.h"
#include "Timer.h"
#include "Textures.h"
#include "Menu.h"
#include "HUD.h"
#include "Result.h"
#include "Collisions.h"
#include "Sounds.h"



#ifndef GAME_H
#define GAME_H

/** Declaration of Game engine class
@author Michal Pawlowski
@date 2021-05-11
*/

class Game {

	/** define end of the game */
	bool isGameStarted = false;
	/** define end of the game */
	bool isGameEnded = false;
	/** define start of new game */
	bool isNewGameStarted = false;
	/** define is music is playing */
	bool isMusicActive = true;
	/** SFML utilities */
	SfmlUtilities utilities;
	/** frame duration counter */
	Timer timer;
	/** textures container */
	Textures textures;
	/** sounds cointainer */
	Sounds sounds;
	/** Menu container */
	Menu* menu;
	/** Head-Up Display */
	HUD* hud;
	/** result container */
	Result result;
	/** player object */
	Player* player;
	/** ufo object */
	Ufo* ufo;
	/** walls container */
	Walls* walls;
	/** bullets container */
	PlayerBullets* bullets;
	/** group of enemy object*/
	Enemies* enemies;
	/** collision operator */
	Collision* collision;

	/** update input signals */
	void updateInput();
	/** create new game */
	void newGame();
	/** update start menu */
	void updateStartMenu();
	/** update game */
	void updateGame();
	/** update end menu */
	void updateEndMenu();
	/** render game and end menu */
	void renderGame();
	/** stop all sounds */
	void stopSounds();
	/** starts music */
	void startSounds();

public:

	/** no argument constructor */
	Game();
	/** destructor */
	~Game();
	/** return information is program window open */
	const bool isWindowOpened() const;
	/** update events */
	void update();
	/** render current state */
	void render();
	
};

#endif

