#pragma once

/*@author Michal Pawlowski*/
/*@file Walls.h*/

#include "Wall.h"

#ifndef WALLS_H
#define WALLS_H

typedef vector<Wall>::iterator wallVectorIt;

/** Declaration of Walls class
@author Michal Pawlowski
@date 2021-05-11
*/
class Walls {

	/** map with textures */
	map<string, sf::Texture*> textures;
	/** vactor with walls */
	vector<Wall> walls;
	/** create walls */
	void createWalls();
	/** delete all walls */
	void deleteAllWalls();

	void initializeTexturesMap(sf::Texture* square1, sf::Texture* square2, sf::Texture* square3, sf::Texture* square4, sf::Texture* triangle1, sf::Texture* triangle2, sf::Texture* triangle3, sf::Texture* triangle4);

public:

	/** construcor */
	Walls(sf::Texture* square1, sf::Texture* square2, sf::Texture* square3, sf::Texture* square4, sf::Texture* triangle1, sf::Texture* triangle2, sf::Texture* triangle3, sf::Texture* triangle4);
	/** delete and the create new walls */
	void rebuiltWalls();
	/** give acces to vector with walls */
	vector<Wall>& getWalls();
	/** give acces to vector with textures */
	map<string, sf::Texture*>& getTextures();
	/**render all walls */
	void renderWalls(sf::RenderWindow* window);

};

#endif