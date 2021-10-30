/*@author Michal Pawlowski*/
/*@file Block.cpp*/

#include "Block.h"

Block::Block(sf::Texture* texture, bool isSquareParam, float xPos, float yPos, float rotation) : isSquare(isSquareParam) {

	sprite.setTexture(*texture);
	sprite.scale(0.3f, 0.3f);
	sprite.setPosition(xPos, yPos);
	sprite.setRotation(rotation);
}

const sf::FloatRect Block::getBounds() const {

	return sprite.getGlobalBounds();
}

bool Block::getIsSquare() const {

	return isSquare;
}

float Block::getSpriteRotation() const {

	return sprite.getRotation();
}

int& Block::getStageAccess() {

	return stage;
}

void Block::setNewTexture(sf::Texture* newTexture) {

	sprite.setTexture(*newTexture);
}

void Block::render(sf::RenderWindow* window) const {

	window->draw(sprite);
}
