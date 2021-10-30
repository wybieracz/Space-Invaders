#pragma once

/*@author Michal Pawlowski*/
/*@file Player.h*/

#include "Unit.h"

#ifndef PLAYER_H
#define PLAYER_H

/** Declaration of Player class
@author Michal Pawlowski
@date 2021-05-11
*/
class Player : public Unit {

	/**health */
	int health;
	/** second texture */
	sf::Texture* texture2;

	/** update time to attack */
	void updateTimeToAttack(float deltaTime);
	/** update information about input events */
	void updateInput(float deltaTime);
	/** check collision with left border */
	bool checkLeftBorderCollision();
	/** check collision with right border */
	bool checkRightBorderCollision();

public:

	/** no argument constructor */
	Player(sf::Texture* cannonTexture, sf::Texture* destroyedCannonTexture);
	/** return value of player health */
	int getHealth();
	/** decrease value of player health */
	void decreaseHealth();
	/** decrease value of player health */
	void increaseHealth();
	/** inform is attack possible */
	const bool isAttackPossible();
	/** update state */
	void update(float deltaTime);
	/** set new cannon texture */
	void setNewCannon();
};

#endif