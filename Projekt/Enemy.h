#pragma once

/*@author Michal Pawlowski*/
/*@file Enemy.h*/

#include <iostream>
#include "Unit.h"

#ifndef ENEMY_H
#define ENEMY_H

enum enemyType { octopus, crab, squid };

/** Declaration of Enemy virtual class
@author Michal Pawlowski
@date 2021-05-11
*/
class Enemy : public Unit {

	/** update time to attack */
	void updateTimeToAttack(float deltaTime);
	/** update position of enemy */
	void updatePosition(float deltaTime, bool leftDirection);
	/** update position under attack */
	virtual void updatePositionUnderSoloAttack(float deltaTime) = 0;
	/** make decision if enemy make solo attack */
	void makeSoloAttackDecision();
	/** animate enemy */
	void animate(float deltaTime);

protected:

	/** second texture */
	sf::Texture* texture2;
	/** define type of alien */
	enemyType type;
	/** define is enemy under solo attack */
	bool underSoloAttack = false;
	/** define time to change texture */
	float timeToAnimate = 10.f;

public:

	/** no argument constructor */
	Enemy();
	/** inform is attack possible */
	const bool isAttackPossible();
	/** update state */
	void update(float deltaTime, bool leftDirection);
	/** checks if object collide with vertical window borderline */
	bool checkSideBorderCollision(bool leftDirection);
	/** checks if object collide with horizontal window borderline */
	bool checkBottomBorderCollision();
	/** moves enemy to lower row */
	void moveToLowerRow();
	/** return type of alien */
	enemyType getEnemyType();
};

#endif