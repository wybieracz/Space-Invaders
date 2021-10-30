#pragma once

/*@author Michal Pawlowski*/
/*@file Player.h*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef UNIT_H
#define UNIT_H

/** Declaration of Unit virtual class
@author Michal Pawlowski
@date 2021-05-11
*/
class Unit {

protected:

	/** representation of a texture */
	sf::Sprite sprite;
	/** texture object */
	sf::Texture* texture;
	/** define movement speed */
	float movementSpeed;
	/** time to next attack */
	float timeToAttack;

	/** sprite initialization */
	void initializeSprite(float xScale, float yScale);

public:

	/** give information about unit position */
	const sf::Vector2f& getPosition() const;
	/** give info about sprite coverage */
	const sf::FloatRect getBounds() const;
	/** inform is attack possible */
	virtual const bool isAttackPossible() = 0;
	/** renders object current state */
	void render(sf::RenderTarget* target);
};

#endif