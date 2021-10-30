/*@author Michal Pawlowski*/
/*@file Wall.cpp*/

#include "Wall.h"
#include <iostream>

void Wall::pushDefaultBlock(float& xPos, float& yPos, float xPosParam, sf::Texture* square, int i) {	// initialize squre block

	wall.push_back(Block(square, true, xPos, yPos, 0.f));

	if (i == 9) {

		xPos = xPosParam - 30.f;
		yPos += 30.f;
	}
}

void Wall::push4thBlock(float& xPos, float& yPos, float xPosParam, sf::Texture* triangle) {	// initialize 4th (trinagle) block

	xPos += 30.f;
	wall.push_back(Block(triangle, false, xPos, yPos, 90.f));
	xPos = xPosParam - 30.f;
	yPos += 30.f;
}

void Wall::push11thBlock(float& xPos, float& yPos, sf::Texture* triangle) {	// initialize 11th (trinagle) block

	xPos += 30.f;
	yPos += 30.f;
	wall.push_back(Block(triangle, false, xPos, yPos, 180.f));
}

void Wall::push13thBlock(float& xPos, float& yPos, sf::Texture* triangle) {	// initialize 13th (trinagle) block

	xPos -= 30.f;
	wall.push_back(Block(triangle, false, xPos, yPos, 270.f));
	yPos -= 30.f;
}

Wall::Wall(float xPosParam, sf::Texture* square, sf::Texture* triangle) {	// built wall

	float xPos = xPosParam;
	float yPos = 750.f;

	for (int i = 0; i < 15; xPos += 30.f, i++) {

		switch (i) {

		case 0: wall.push_back(Block(triangle, false, xPos, yPos, 0.f)); break;
		case 4: push4thBlock(xPos, yPos, xPosParam, triangle); break;
		case 11: push11thBlock(xPos, yPos, triangle); break;
		case 13: push13thBlock(xPos, yPos, triangle); break;
		case 12: continue; break;
		default: pushDefaultBlock(xPos, yPos, xPosParam, square, i); break;
		}
	}
}

vector<Block>& Wall::getWall() {
	
	return wall;
}

void Wall::renderWall(sf::RenderWindow* window) const {

	for (const auto& i : wall) i.render(window);	// render all blocks
}
