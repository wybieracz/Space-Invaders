#pragma once

/*@author Michal Pawlowski*/
/*@file EnemyBullet.h*/

#include <SFML/Graphics.hpp>

#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

/** Declaration of EnemyBullets class
@author Michal Pawlowski
@date 2021-05-11
*/
class EnemyBullet {

	/** rectangle shape object */
	sf::Sprite sprite;
	/** give information about bullet position */
	sf::Vector2f direction;
	/** define bullet movement speed */
	float movementSpeed;

public:

	/** construcor */
	EnemyBullet(float xPosition, float yPosition, float xDirection, float yDirection, sf::Texture* texture);
	/** give info about shape coverage */
	const sf::FloatRect getBounds() const;
	/** update bullet sate */
	void update(float deltaTime);
	/** render bullet */
	void render(sf::RenderTarget* target) const;
};

#endif