#pragma once

/*@author Michal Pawlowski*/
/*@file Block.h*/

#include <SFML/Graphics.hpp>

#ifndef BLOCK_H
#define BLOCK_H

/** Declaration of Walls class
@author Michal Pawlowski
@date 2021-05-11
*/
class Block {

	/** representation of a texture */
	sf::Sprite sprite;
	/** defines shape */
	bool isSquare;
	/** destruction stage */
	int stage = 1;

public:

	/** constructor */
	Block(sf::Texture* texture, bool isSquareParam, float xPos, float yPos, float rotation);
	/** give info about sprite coverage */
	const sf::FloatRect getBounds() const;
	/** give information about shape */
	bool getIsSquare() const;
	/** give information about sprite rotation */
	float getSpriteRotation() const;
	/** give access to stage */
	int& getStageAccess();
	/** set new texture */
	void setNewTexture(sf::Texture* newTexture);
	/** draw whis object */
	void render(sf::RenderWindow* window) const;
};

#endif