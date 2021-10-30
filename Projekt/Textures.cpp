/*@author Michal Pawlowski*/
/*@file Textures.cpp*/

#include "Textures.h"

Textures::Textures() {

	initializeTextures();
	initializeFont("Fonts/regular.ttf");
}

Textures::~Textures() {

	// removing textures
	for (auto& i : textures) delete i.second;
	textures.clear();
}

void Textures::initializeTexture(const string name, const string fileName) {

	textures[name] = new sf::Texture();	// create new empty texture

	try {

		if (!textures[name]->loadFromFile(fileName)) throw 2;	// load texture from file
	}
	catch (int errorNumber) {

		if (errorNumber == 2) {

			std::cerr << "ERROR[2]: Unable to open texture." << std::endl;	// error message if unable to open file
			exit(errorNumber);
		}
	}
}

void Textures::initializeEnemyTextures() {

	// initialize enemy textures

	initializeTexture("octopus1", "Textures/Enemy/Octopus_1.png");
	initializeTexture("octopus2", "Textures/Enemy/Octopus_2.png");
	initializeTexture("crab1", "Textures/Enemy/Crab_1.png");
	initializeTexture("crab2", "Textures/Enemy/Crab_2.png");
	initializeTexture("squid1", "Textures/Enemy/Squid_1.png");
	initializeTexture("squid2", "Textures/Enemy/Squid_2.png");
	initializeTexture("enemy_bullet", "Textures/Enemy/Enemy_bullet.png");
	initializeTexture("ufo", "Textures/Enemy/Ufo.png");
}

void Textures::initializeWallTextures() {

	// initialize wall textures

	initializeTexture("square1", "Textures/Wall/Square_wall_1.png");
	initializeTexture("square2", "Textures/Wall/Square_wall_2.png");
	initializeTexture("square3", "Textures/Wall/Square_wall_3.png");
	initializeTexture("square4", "Textures/Wall/Square_wall_4.png");
	initializeTexture("triangle1", "Textures/Wall/Triangle_wall_1.png");
	initializeTexture("triangle2", "Textures/Wall/Triangle_wall_2.png");
	initializeTexture("triangle3", "Textures/Wall/Triangle_wall_3.png");
	initializeTexture("triangle4", "Textures/Wall/Triangle_wall_4.png");
}

void Textures::initializeTextures() {

	// initialize all textures

	initializeTexture("start", "Textures/Menu/Start.png");
	initializeTexture("end", "Textures/Menu/End.png");

	initializeTexture("cannon", "Textures/Cannon/Cannon.png");
	initializeTexture("destroyed_cannon", "Textures/Cannon/Cannon_destroyed.png");

	initializeEnemyTextures();
	initializeWallTextures();
}

void Textures::initializeFont(const string fileName) {

	try {

		if (!regular.loadFromFile(fileName)) throw 3; // open font from file
	}
	catch (int errorNumber) {

		if (errorNumber == 3) {

			std::cerr << "ERROR[3]: Unable to open font file." << std::endl;	// error message if unable to open file
			exit(errorNumber);
		}
	}
}

sf::Texture* Textures::getTexture(string key) {

	return textures[key];
}

sf::Font* Textures::getFont() {

	return &regular;
}
