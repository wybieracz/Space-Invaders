/*@author Michal Pawlowski*/
/*@file Time.cpp*/

#include "Timer.h"

Timer::Timer() {

	deltaTime = clock.restart().asSeconds();	// set deltaTime
}

Timer::~Timer() {

}

void Timer::CalculateDeltaTime() {

	deltaTime = clock.restart().asSeconds();	// reset deltaTime
}

float Timer::getDeltaTime() {

	return deltaTime;
}
