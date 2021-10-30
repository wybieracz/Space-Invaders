#pragma once

/*@author Michal Pawlowski*/
/*@file Player.h*/

#include "Unit.h"

#ifndef UFO_H
#define UFO_H

/** Declaration of Ufo class
@author Michal Pawlowski
@date 2021-05-11
*/
class Ufo : public Unit {

	/** define is ufo under attack */
	bool underAttack = false;
	/** sound of ufo attack */
	sf::Sound ufoSound;

	/** initialize ufo sound */
	void initializeSound(sf::SoundBuffer* ufoSoundParam);
	/** update time to attack */
	void updateTimeToAttack(float deltaTime);
	/** set ufo position to start */
	void setStartPosition();
	/** check if ufo is out of screen */
	void checkBorder();
	/** inform is attack possible */
	const bool isAttackPossible();

public:

	/** constructor */
	Ufo(sf::Texture* ufoTexture, sf::SoundBuffer* ufoSoundParam);
	/** update ufo status */
	void update(float deltaTime);
	/** set ufo in default stage */
	void reset();
	/** renders ufo current state */
	void render(sf::RenderTarget* target);
	/** stop ufo sound */
	void stopUfoSound();
};

#endif