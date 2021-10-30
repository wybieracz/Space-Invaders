/*@author Michal Pawlowski*/
/*@file HUD.cpp*/

#include "HUD.h"

HUD::HUD(sf::Texture* texture, sf::Font* font) {

	regular = *font;
	initializeTexts();
	initializeBanner();
	initializeBar(texture);
}

void HUD::initializeBanner() { // initialize upper banner

	banner[0].setSize(sf::Vector2f(1920.f, 60.f));
	banner[0].setFillColor(sf::Color::Black);
	banner[1].setFillColor(sf::Color::White);
	banner[1].setSize(sf::Vector2f(1920.f, 2.f));
	banner[1].setPosition(0.f, 59.f);
}

void HUD::initializeTexts() {

	hudText.insert(pair<string, sf::Text>("score", initializeText(regular, 30, sf::Color::White, "Score:", 50.f, 10.f)));	// score
	hudText.insert(pair<string, sf::Text>("scoreValue", initializeText(regular, 30, sf::Color::Green, "0", 160.f, 10.f)));	// score value
	hudText.insert(pair<string, sf::Text>("level", initializeText(regular, 30, sf::Color::White, "Level:", 830.f, 10.f)));	// level
	hudText.insert(pair<string, sf::Text>("levelValue", initializeText(regular, 30, sf::Color::Green, "0", 930.f, 10.f)));	// level value
	hudText.insert(pair<string, sf::Text>("health", initializeText(regular, 30, sf::Color::White, "Health:", 1530.f, 10.f)));	// health
}

sf::Text HUD::initializeText(sf::Font& font, unsigned int fontSize, sf::Color color, string value, float xPos, float yPos) {

	sf::Text temp; // create empty text

	temp.setString(value);
	temp.setFont(font);
	temp.setCharacterSize(fontSize);
	temp.setFillColor(color);
	temp.setPosition(xPos, yPos);

	return temp;	// return created text
}

void HUD::initializeBar(sf::Texture* texture) {

	float xPos = 1640.f;

	for (int i = 0; i < 4; i++, xPos += 60.f) {

		health[i].setTexture(*texture);
		health[i].setScale((float)0.18, (float)0.18);
		health[i].setPosition(xPos, 15.f);
	}
}

void HUD::updateHUD(int score, int level) {

	hudText["scoreValue"].setString(to_string(score)); // convert score value to HUD text
	hudText["levelValue"].setString(to_string(level - 1));	// convert level value to HUD text
}

void HUD::renderHUD(sf::RenderWindow* windowPtr, int playerHealth) {	// render HUD

	windowPtr->draw(banner[0]);
	windowPtr->draw(banner[1]);

	for (const auto& i : hudText) windowPtr->draw(i.second);
	
	renderHealthBar(windowPtr, playerHealth);
}

void HUD::renderHealthBar(sf::RenderWindow* windowPtr, int playerHealth) {

	for (int i = 0; i < playerHealth; i++) windowPtr->draw(health[i]);
}
