/*@author Michal Pawlowski*/
/*@file Menu.cpp*/

#include "Menu.h"
#include <iostream>
void Menu::initializeBorads(sf::Texture* start, sf::Texture* end) {

	board[0].setTexture(*start);
	board[0].setScale(1.f, 1.f);
	board[0].setPosition(592.f, 365.f);
	board[1].setTexture(*end);
	board[1].setScale(1.f, 1.f);
	board[1].setPosition(320.f, 180.f);
}

void Menu::initializeText(sf::Text& text, sf::Font& font, unsigned int fontSize, sf::Color color, string value, float xPos, float yPos) {

	text.setString(value);
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(color);
	text.setPosition(xPos, yPos);
}

void Menu::initializeTexts(sf::Font* font) {

	initializeText(text[0], *font, 20, sf::Color::White, "Press ENTER to play!", 965.f, 800.f);
	text[0].setOrigin(104.f, 8.f);
	initializeText(text[1], *font, 65, sf::Color::White, "0", 960.f, 490.f);
	initializeText(text[2], *font, 50, sf::Color::Green, "0", 960.f, 620.f);
}

void Menu::scaleText(float deltaTime) {

	if (text[0].getScale().x < 1) sizeUp = true;
	if (text[0].getScale().x > 1.2) sizeUp = false;

	if (sizeUp) text[0].setScale(text[0].getScale().x * (0.994 + deltaTime), text[0].getScale().y * (0.994 + deltaTime));	// size up text (animation)
	else text[0].setScale(text[0].getScale().x * (1.006 - deltaTime), text[0].getScale().y * (1.006 - deltaTime));	// size down text (animation)
}

void Menu::updateScore(int score, int bestScore) {

	text[1].setString(to_string(score));
	text[1].setPosition(960.f - text[1].getGlobalBounds().width / 2, 490.f);
	text[2].setString(to_string(bestScore));
	text[2].setPosition(960.f - text[2].getGlobalBounds().width / 2, 620.f);
}

Menu::Menu(sf::Texture* start, sf::Texture* end, sf::Font* font) {
	 
	initializeBorads(start, end);
	initializeTexts(font);
}

void Menu::startMenu(sf::RenderWindow* window) {

	window->draw(board[0]);
	window->draw(text[0]);	
}

void Menu::endMenu(sf::RenderWindow* window) {

	window->draw(board[1]);
	window->draw(text[1]);
	window->draw(text[2]);
}
