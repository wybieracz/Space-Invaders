/*@author Michal Pawlowski*/
/*@file Ufo.cpp*/

#include "Ufo.h"
#include <iostream>
#define UFO_SPEED 400.f
#define UFO_ATTACK_SPEED 100.f
#define UFO_TIME_TO_ATTACK 1000.f

void Ufo::initializeSound(sf::SoundBuffer* ufoSoundParam) {

	ufoSound.setBuffer(*ufoSoundParam);
	ufoSound.setVolume(20.f);
}

void Ufo::updateTimeToAttack(float deltaTime) {

	if (timeToAttack > 0) timeToAttack -= UFO_ATTACK_SPEED * deltaTime;	// decrement ufo time to attack
	else {

		underAttack = true;
		ufoSound.play();	// play ufo sound if under attack
	}
}

Ufo::Ufo(sf::Texture* ufoTexture, sf::SoundBuffer* ufoSoundParam) {

	texture = ufoTexture;

	initializeSprite(0.2f, 0.2f);
	setStartPosition();
	initializeSound(ufoSoundParam);

	movementSpeed = UFO_SPEED;
	timeToAttack = UFO_TIME_TO_ATTACK;
}

void Ufo::update(float deltaTime) {

	checkBorder();	// check is ufo out of the screen
	if(!underAttack) updateTimeToAttack(deltaTime);
	else sprite.move(-movementSpeed * deltaTime, 0.f);
}

void Ufo::setStartPosition() {

	sprite.setPosition(1940.f, 80.f);	// set ufo start position
}

void Ufo::render(sf::RenderTarget* target) {

	if(underAttack) target->draw(sprite);	// render ufo
}

void Ufo::stopUfoSound() {

	if(ufoSound.getStatus() == sf::SoundSource::Playing) ufoSound.stop();
}

void Ufo::checkBorder() {

	if (sprite.getGlobalBounds().left < -30.f) reset();
}

const bool Ufo::isAttackPossible() {

	if (timeToAttack <= 0) {

		timeToAttack = 50.f;
		return true;
	}
	else return false;
}

void Ufo::reset() {

	underAttack = false;
	timeToAttack = UFO_TIME_TO_ATTACK;
	setStartPosition();	// set ufo start position
	ufoSound.stop();	// stop ufo sound
}
