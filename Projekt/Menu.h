#pragma once

/*@author Michal Pawlowski*/
/*@file Menu.h*/

#include <SFML/Graphics.hpp>

using namespace std;

#ifndef MENU_H
#define MENU_H

/** Declaration of Menu class
@author Michal Pawlowski
@date 2021-05-11
*/
class Menu {

	/** table with start and end board */
	sf::Sprite board[2];
	/** table with menu texts */
	sf::Text text[3];
	/** define text animation */
	bool sizeUp = true;

	/** initialize menu boards */
	void initializeBorads(sf::Texture* start, sf::Texture* end);
	/** initialize single menu text */
	void initializeText(sf::Text& text, sf::Font& font, unsigned int fontSize, sf::Color color, string value, float xPos, float yPos);
	/** initialize menu texts */
	void initializeTexts(sf::Font* font);

public:

	/** constructor */
	Menu(sf::Texture* start, sf::Texture* end, sf::Font* font);
	/** displays start menu */
	void startMenu(sf::RenderWindow* window);
	/** displays end menu */
	void endMenu(sf::RenderWindow* window);
	/** scale menu text */
	void scaleText(float deltaTime);
	/** save score to displayed text */
	void updateScore(int score, int bestScore);
};

#endif