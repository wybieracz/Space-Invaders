/*@author Michal Pawlowski*/
/*@file Octopus.cpp*/

#include "Octopus.h"

void Octopus::updatePositionUnderSoloAttack(float deltaTime) {

	if (sprite.getGlobalBounds().top < 800.f) sprite.move(0.f, movementSpeed * 1.5 * deltaTime);
	else sprite.move(0.f, movementSpeed * deltaTime);
}

Octopus::Octopus(sf::Texture* crab1, sf::Texture* crab2, float x, float y) {

	texture = crab1;
	texture2 = crab2;
	type = octopus;

	initializeSprite(0.2f, 0.2f);
	sprite.setPosition(x, y);
}