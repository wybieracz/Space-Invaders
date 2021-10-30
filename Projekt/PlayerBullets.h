#pragma once

/*@author Michal Pawlowski*/
/*@file Bullets.h*/

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include "PlayerBullet.h"

using namespace std;

#ifndef PLAYER_BULLETS_H
#define PLAYER_BULLETS_H

typedef vector<PlayerBullet>::iterator playerBulletIt;

/** Declaration of PlayerBullets class
@author Michal Pawlowski
@date 2021-05-11
*/
class PlayerBullets {

	/** vector of constructed bullets */
	vector<PlayerBullet> bullets;
	/** sound of shooting */
	sf::Sound shootSound;

public:

	/** constructor */
	PlayerBullets(sf::SoundBuffer* shootSoundParam);
	/** destructor */
	~PlayerBullets();
	/** update bullets status */
	void updateBullets(float deltaTime);
	/** add new bullet */
	void spawnBullet(float xPos);
	/** render bullets */
	void renderBullets(sf::RenderWindow* windowPtr) const;
	/** give access to bullets vector */
	vector<PlayerBullet>& getBulletsVector();
	/** delete all bullets */
	void deleteAllBullets();
};

#endif