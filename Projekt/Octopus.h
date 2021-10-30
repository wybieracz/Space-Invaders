#pragma once

/*@author Michal Pawlowski*/
/*@file Octopus.h*/

#include "Enemy.h"

#ifndef OCTOPUS_H
#define OCTOPUS_H

/** Declaration of Enemy class
@author Michal Pawlowski
@date 2021-05-11
*/

class Octopus : public Enemy {

	void updatePositionUnderSoloAttack(float deltaTime);

public:

	Octopus(sf::Texture* crab1, sf::Texture* crab2, float x, float y);
};

#endif
