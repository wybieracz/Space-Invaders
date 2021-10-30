#pragma once

/*@author Michal Pawlowski*/
/*@file Squid.h*/

#include "Enemy.h"

#ifndef SQUID_H
#define SQUID_H

/** Declaration of Enemy class
@author Michal Pawlowski
@date 2021-05-11
*/

class Squid : public Enemy {

	void updatePositionUnderSoloAttack(float deltaTime);

public:

	Squid(sf::Texture* crab1, sf::Texture* crab2, float x, float y);
};

#endif