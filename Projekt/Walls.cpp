/*@author Michal Pawlowski*/
/*@file Walls.cpp*/

#include "Walls.h"

void Walls::initializeTexturesMap(sf::Texture* square1, sf::Texture* square2, sf::Texture* square3, sf::Texture* square4, sf::Texture* triangle1, sf::Texture* triangle2, sf::Texture* triangle3, sf::Texture* triangle4) {

	textures.insert(pair<string, sf::Texture*>("square1", square1));
	textures.insert(pair<string, sf::Texture*>("square2", square2));
	textures.insert(pair<string, sf::Texture*>("square3", square3));
	textures.insert(pair<string, sf::Texture*>("square4", square4));
	textures.insert(pair<string, sf::Texture*>("triangle1", triangle1));
	textures.insert(pair<string, sf::Texture*>("triangle2", triangle2));
	textures.insert(pair<string, sf::Texture*>("triangle3", triangle3));
	textures.insert(pair<string, sf::Texture*>("triangle4", triangle4));
}

Walls::Walls(sf::Texture* square1, sf::Texture* square2, sf::Texture* square3, sf::Texture* square4, sf::Texture* triangle1, sf::Texture* triangle2, sf::Texture* triangle3, sf::Texture* triangle4) {

	initializeTexturesMap(square1, square2, square3, square4, triangle1, triangle2, triangle3, triangle4);
	createWalls();
}

void Walls::rebuiltWalls() {

	deleteAllWalls();
	createWalls();
}

void Walls::createWalls() {

	float xPos = 195.f;

	for (int i = 0; i < 5; i++, xPos += 345) walls.push_back(Wall(xPos, textures["square1"], textures["triangle1"]));
}

void Walls::deleteAllWalls() {

	for (wallVectorIt i = walls.begin(); i != walls.end(); i++) { // iterate over walls

		(*i).getWall().clear();	// delete whole wall
	}

	walls.clear();
}

vector<Wall>& Walls::getWalls() {
	
	return walls;
}

map<string, sf::Texture*>& Walls::getTextures() {

	return textures;
}

void Walls::renderWalls(sf::RenderWindow* window) {

	for (const auto& i : walls) i.renderWall(window);	// render single wall
}
