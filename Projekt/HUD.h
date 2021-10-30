#pragma once

/*@author Michal Pawlowski*/
/*@file HUD.h*/

#include <map>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#ifndef HUD_H
#define HUD_H

using namespace std;

/** Declaration of HUD class
@author Michal Pawlowski
@date 2021-05-11
*/
class HUD {

	/** font object */
	sf::Font regular;
	/** level text */
	map<string, sf::Text> hudText;
	/** upper banner */
	sf::RectangleShape banner[2];
	/** player health bar */
	sf::Sprite health[4];

	/** initialize upper banner */
	void initializeBanner();
	/** initialize HUD texts */
	void initializeTexts();
	/** initialize single text */
	sf::Text initializeText(sf::Font& font, unsigned int fontSize, sf::Color color, string value, float xPos, float yPos);
	/** initialize health bar */
	void initializeBar(sf::Texture* texture);

public:

	/** constructor */
	HUD(sf::Texture* texture, sf::Font* font);
	/** updates HUD information */
	void updateHUD(int score, int level);
	/** render HUD */
	void renderHUD(sf::RenderWindow* windowPtr, int playerHealth);
	/** render health bar */
	void renderHealthBar(sf::RenderWindow* windowPtr, int playerHealth);
};

#endif