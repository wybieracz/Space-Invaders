#pragma once

/*@author Michal Pawlowski*/
/*@file EnemyBullets.h*/
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "EnemyBullet.h"

using namespace std;

#ifndef ENEMY_BULLETS_H
#define ENEMY_BULLETS_H

typedef vector<EnemyBullet>::iterator enemyBulletIt;

/** Declaration of EnemyBullets class
@author Michal Pawlowski
@date 2021-05-11
*/
class EnemyBullets {


	/** vector of constructed bullets */
	vector<EnemyBullet> bullets;
	/** pointer to enemy bullet texture */
	sf::Texture* bulletTexture;

public:

	/** constructor */
	EnemyBullets(sf::Texture* texture);
	/** destructor */
	~EnemyBullets();
	/** update bullets status */
	void updateBullets(float deltaTime);
	/** add new bullet */
	void spawnBullet(float xPos, float yPos);
	/** render bullets */
	void renderBullets(sf::RenderWindow* windowPtr) const;
	/** give access to bullets vector */
	vector<EnemyBullet>& getBulletsVector();
	/** delete all enemy bullets */
	void deleteAllEnemyBullets();

};

#endif