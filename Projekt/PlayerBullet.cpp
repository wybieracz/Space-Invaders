/*@author Michal Pawlowski*/
/*@file PlayerBullet.cpp*/

#include "PlayerBullet.h"

#define PLAYER_BULLET_SPEED 600.f

PlayerBullet::PlayerBullet(float xPosition, float yPosition, float xDirection, float yDirection) {

	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(3.f, 15.f));
	shape.setPosition(xPosition, yPosition);
	direction.x = xDirection;
	direction.y = yDirection;
	movementSpeed = PLAYER_BULLET_SPEED;
}

const sf::FloatRect PlayerBullet::getBounds() const {

	return shape.getGlobalBounds();
}

void PlayerBullet::update(float deltaTime) {

	shape.move(movementSpeed * direction * deltaTime);
}

void PlayerBullet::render(sf::RenderTarget* target) const {

	target->draw(shape);
}