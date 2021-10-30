/*@author Michal Pawlowski*/
/*@file Unit.cpp*/

#include "Unit.h"

void Unit::initializeSprite(float xScale, float yScale) {
	
	sprite.setTexture(*texture);	// set texture
	sprite.scale(xScale, yScale);	// set size of texture
}

const sf::Vector2f& Unit::getPosition() const {
	
	return sprite.getPosition();
}

const sf::FloatRect Unit::getBounds() const {

	return sprite.getGlobalBounds();
}

void Unit::render(sf::RenderTarget* target) {

	target->draw(sprite);
}
