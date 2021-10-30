#pragma once

/*@author Michal Pawlowski*/
/*@file Textures.h*/

#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef TEXTURES_H
#define TEXTURES_H

using namespace std;

/** Declaration of Textures class
@author Michal Pawlowski
@date 2021-05-11
*/
class Textures {

	/** map which include all textures */
	map<string, sf::Texture*> textures;
	/** font object */
	sf::Font regular;

	/** initialize singe texture */
	void initializeTexture(const string name, const string fileName);
	/** initialize enemy textures */
	void initializeEnemyTextures();
	/** initialize wall textures */
	void initializeWallTextures();
	/** initialize textures */
	void initializeTextures();
	/** initialize fonts */
	void initializeFont(const string fileName);

public:

	/** no argument constructor */
	Textures();
	/** desctructor */
	~Textures();
	/** give access to texture pointer */
	sf::Texture* getTexture(string key);
	/** give access to font pointer */
	sf::Font* getFont();
};

#endif