#pragma once

/*@author Michal Pawlowski*/
/*@file PlayerBullet.h*/

#include <SFML/Graphics.hpp>

#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H

/** Declaration of PlayerBullet class
@author Michal Pawlowski
@date 2021-05-11
*/
class PlayerBullet {

	/** rectangle shape object */
	sf::RectangleShape shape;
	/** give information about bullet position */
	sf::Vector2f direction;
	/** define bullet movement speed */
	float movementSpeed;

public:

	/** construcor */
	PlayerBullet(float xPosition, float yPosition, float xDirection, float yDirection);
	/** give info about shape coverage */
	const sf::FloatRect getBounds() const;
	/** update bullet sate */
	void update(float deltaTime);
	/** render bullet */
	void render(sf::RenderTarget* target) const;
};

#endif