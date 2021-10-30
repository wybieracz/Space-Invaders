/*@author Michal Pawlowski*/
/*@file Octopus.cpp*/

#include "Squid.h"

void Squid::updatePositionUnderSoloAttack(float deltaTime) {

	if(sprite.getGlobalBounds().top < 800.f) sprite.move(0.f, movementSpeed * 3 * deltaTime);
	else sprite.move(0.f, movementSpeed * 1.5 * deltaTime);
}

Squid::Squid(sf::Texture* crab1, sf::Texture* crab2, float x, float y) {

	texture = crab1;
	texture2 = crab2;
	type = squid;

	initializeSprite(0.2f, 0.2f);
	sprite.setPosition(x + 7.f, y);
}