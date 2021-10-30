#pragma once

/*@author Michal Pawlowski*/
/*@file Walls.h*/

#include <vector>
#include "Block.h"

using namespace std;

#ifndef WALL_H
#define WALL_H

typedef vector<Block>::iterator blockVectorIt;

/** Declaration of Wall class
@author Michal Pawlowski
@date 2021-05-11
*/
class Wall {

	vector<Block> wall;

	/** add to vector default block */
	void pushDefaultBlock(float& xPos, float& yPos, float xPosParam, sf::Texture* square, int i);
	/** add to vector 4th block */
	void push4thBlock(float& xPos, float& yPos, float xPosParam, sf::Texture* triangle);
	/** add to vector 11th block */
	void push11thBlock(float& xPos, float& yPos, sf::Texture* triangle);
	/** add to vector 13th block */
	void push13thBlock(float& xPos, float& yPos, sf::Texture* triangle);

public:

	/** constructor */
	Wall(float xPos, sf::Texture* square, sf::Texture* triangle);
	/** give acces to vector of Blocks */
	vector<Block>& getWall();
	/** render single wall */
	void renderWall(sf::RenderWindow* window) const;
};

#endif