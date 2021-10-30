#pragma once

/*@author Michal Pawlowski*/
/*@file Timer.h*/

#include <SFML/System.hpp>

#ifndef TIMER_H
#define TIMER_H

/** Declaration of Timer class
@author Michal Pawlowski
@date 2021-05-11
*/
class Timer {

	/** counter of time of game */
	sf::Clock clock;
	/** time of single frame */
	float deltaTime;

public:

	/** no argument constructor */
	Timer();
	/** destructor */
	~Timer();
	/** calculate time of frame duration */
	void CalculateDeltaTime();
	/** returns deltaTime */
	float getDeltaTime();
};

#endif
