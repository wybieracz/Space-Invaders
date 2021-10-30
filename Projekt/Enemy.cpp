/*@author Michal Pawlowski*/
/*@file Enemy.cpp*/

#include "Enemy.h"

using namespace std;

#define ENEMY_SPEED 60.f
#define ENEMY_ATTACK_SPEED 50.f
#define SOLO_ATTACK_FREQUENCY 5000

Enemy::Enemy() : texture2(nullptr) {
	
	timeToAttack = 50.f + rand() % 1000;	// set random time to attack
	movementSpeed = ENEMY_SPEED;
}

const bool Enemy::isAttackPossible() {

	if (timeToAttack <= 0) {

		timeToAttack = 50.f + rand() % 1000; // set random time to attack
		return true;
	}
	else return false;
}

void Enemy::updateTimeToAttack(float deltaTime) {

	if (timeToAttack > 0) timeToAttack -= ENEMY_ATTACK_SPEED * deltaTime;	// decrease time to attack
}

void Enemy::updatePosition(float deltaTime, bool leftDirection) {

	// move enemy

	if (leftDirection) sprite.move(-movementSpeed * deltaTime, 0.f);
	else  sprite.move(movementSpeed * deltaTime, 0.f);
}

void Enemy::makeSoloAttackDecision() {

	// random decicion if make solo attack

	if (rand() % SOLO_ATTACK_FREQUENCY == 0) {

		underSoloAttack = true;
		sprite.setTexture(*texture2);
	}
}

void Enemy::animate(float deltaTime) {

	// animate enemy

	if (timeToAnimate > 0) timeToAnimate -= 20.f * deltaTime;
	else {

		if (sprite.getTexture() == texture) sprite.setTexture(*texture2);
		else sprite.setTexture(*texture);
		timeToAnimate = 10.f;
	}
}

void Enemy::update(float deltaTime, bool leftDirection) {

	if (!underSoloAttack) {
		updateTimeToAttack(deltaTime);
		updatePosition(deltaTime, leftDirection);
		animate(deltaTime);
		makeSoloAttackDecision();
	}
	else updatePositionUnderSoloAttack(deltaTime);
}

bool Enemy::checkSideBorderCollision(bool leftDirection) {

	// check if enemy is on screen border

	if (!underSoloAttack && (leftDirection && getPosition().x < 0.f) || (!leftDirection && getPosition().x + 45.f > 1920.f)) {

		return true;
	}
	else return false;
}

bool Enemy::checkBottomBorderCollision() {

	// check if enemy is on bottom screen border

	if (getPosition().y > 1060.f) {

		return true;
	}
	else return false;
}

void Enemy::moveToLowerRow() {

	sprite.setPosition(getPosition().x, getPosition().y + 50.f);	// move enemy to lover row
}

enemyType Enemy::getEnemyType() {

	return type;
}
