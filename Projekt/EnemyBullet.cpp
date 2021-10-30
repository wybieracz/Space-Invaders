/*@author Michal Pawlowski*/
/*@file EnemyBullet.cpp*/

#include "EnemyBullet.h"

#define ENEMY_BULLET_SPEED 450.f

EnemyBullet::EnemyBullet(float xPosition, float yPosition, float xDirection, float yDirection, sf::Texture* texture) {

	sprite.setTexture(*texture);
	sprite.scale(0.2, 0.2);
	sprite.setPosition(xPosition, yPosition);
	direction.x = xDirection;
	direction.y = yDirection;
	movementSpeed = ENEMY_BULLET_SPEED;
}

const sf::FloatRect EnemyBullet::getBounds() const {

	return sprite.getGlobalBounds();
}

void EnemyBullet::update(float deltaTime) {

	sprite.move(movementSpeed * direction * deltaTime);
}

void EnemyBullet::render(sf::RenderTarget* target) const {

	target->draw(sprite);
}
