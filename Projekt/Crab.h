#pragma once

/*@author Michal Pawlowski*/
/*@file Crab.h*/

#include "Enemy.h"

#ifndef CRAB_H
#define CRAB_H

/** Declaration of Crab class
@author Michal Pawlowski
@date 2021-05-11
*/

class Crab : public Enemy {

	void updatePositionUnderSoloAttack(float deltaTime);

public:

	Crab(sf::Texture* crab1, sf::Texture* crab2, float x, float y);
};

#endif