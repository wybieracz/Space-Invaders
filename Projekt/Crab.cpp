/*@author Michal Pawlowski*/
/*@file Crab.cpp*/

#include "Crab.h"

void Crab::updatePositionUnderSoloAttack(float deltaTime) {

	// define crab move under solo attack

	if (sprite.getGlobalBounds().top < 800.f) sprite.move(0.f, movementSpeed * 2 * deltaTime);
	else sprite.move(0.f, movementSpeed * 1.2 * deltaTime);
}

Crab::Crab(sf::Texture* crab1, sf::Texture* crab2, float x, float y) {

	texture = crab1;
	texture2 = crab2;
	type = crab;

	initializeSprite(0.2f, 0.2f);
	sprite.setPosition(x + 2.f, y);
}