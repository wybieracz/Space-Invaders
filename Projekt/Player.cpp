/*@author Michal Pawlowski*/
/*@file Player.cpp*/

#include "Player.h"

#define PLAYER_SPEED 600.f
#define ATTACK_SPEED 100.f

Player::Player(sf::Texture* cannonTexture, sf::Texture* destroyedCannonTexture) : health(4) {

	texture = cannonTexture;
	texture2 = destroyedCannonTexture;

	initializeSprite(0.2f, 0.2f);
	sprite.setPosition(934.f, 1050.f);

	movementSpeed = PLAYER_SPEED;
	timeToAttack = 50.f;
}

int Player::getHealth() {
	
	return health;
}

void Player::decreaseHealth() {

	if (health > 0) health -= 1;	// decrease health value
	if (health == 0) sprite.setTexture(*texture2);	// set new player texture if health value equal 0
}

void Player::increaseHealth() {

	if (health < 4) health += 1;	// increase health value
}

const bool Player::isAttackPossible() {

	// shooting cooldown

	if (timeToAttack <= 0) {

		timeToAttack = 50.f;
		return true;
	}
	else return false;
}

void Player::updateTimeToAttack(float deltaTime) {

	if (timeToAttack > 0) timeToAttack -= ATTACK_SPEED * deltaTime;	// decrease time to attack
}

void Player::updateInput(float deltaTime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !checkLeftBorderCollision()) sprite.move(-movementSpeed * deltaTime, 0.f);	// move player left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !checkRightBorderCollision()) sprite.move(movementSpeed * deltaTime, 0.f);	// move player right
}

bool Player::checkLeftBorderCollision() {
	
	// checks collision with left screen border

	if (sprite.getGlobalBounds().left <= 0.f) return true;
	else return false;
}

bool Player::checkRightBorderCollision() {

	// checks collision with right screen border
	
	if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= 1920.f) return true;
	else return false;
}

void Player::update(float deltaTime) {

	updateTimeToAttack(deltaTime);
	updateInput(deltaTime);
}

void Player::setNewCannon() {

	sprite.setTexture(*texture);
	health = 4;
}
