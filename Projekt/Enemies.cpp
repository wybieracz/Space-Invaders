/*@author Michal Pawlowski*/
/*@file Bullet.cpp*/

#include "Enemies.h"

void Enemies::spawnBullet(Enemy* enemy) {

	if ((*enemy).isAttackPossible()) bullets->spawnBullet((*enemy).getBounds().left, (*enemy).getBounds().top);	// spawn enemy bullet
}

Enemies::Enemies(sf::Texture* octopus1, sf::Texture* octopus2, sf::Texture* crab1, sf::Texture* crab2, sf::Texture* squid1, sf::Texture* squid2, sf::Texture* enemyBullet) : level(-1), leftDirection(false), bullets(nullptr) {

	textures.insert(pair<string, sf::Texture*>("octopus1", octopus1));
	textures.insert(pair<string, sf::Texture*>("octopus2", octopus2));
	textures.insert(pair<string, sf::Texture*>("crab1", crab1));
	textures.insert(pair<string, sf::Texture*>("crab2", crab2));
	textures.insert(pair<string, sf::Texture*>("squid1", squid1));
	textures.insert(pair<string, sf::Texture*>("squid2", squid2));
	
	bullets = new EnemyBullets(enemyBullet);
}

Enemies::~Enemies() {

	deleteAllEnemiesAndBullets();

	textures.clear();
	delete bullets;
}

void Enemies::update(int& level, bool& isGameEnded, PlayerBullets& playerBullets, float deltaTime) {

	if (mainList.empty()) {	// if all enemies destroyed

		level++;
		leftDirection = false;
		playerBullets.deleteAllBullets();
		createWave();
	}

	updateGroupState(isGameEnded, deltaTime);	// update all enemies
	borderCollisionsCheck();	// check collisions with screen borders
	bullets->updateBullets(deltaTime);	// update enemiy bullets states
}

void Enemies::createWave() {	// create new enemy wave

	level++;
	float yPos = 130.f;

	createSector(squid, yPos);	// create rows with squids
	createSector(crab, yPos);	// create rows with crabs
	createSector(octopus, yPos);	// create rows with octopuses
}

void Enemies::createSector(enemyType type, float& yPos) {

	for (int i = (level % 100) / 30 + 1 + additionalRow(level, type); i > 0; i--) {

		mainList.push_back(createRow(level, type, yPos));	// add single enemy to list
		yPos += 50.f;
	}
}

list<Enemy*> Enemies::createRow(int level, enemyType type, float yPos) {

	list<Enemy*> buffer;
	
	switch (type) {

	case squid: createSquidRow(level, yPos, buffer); break;	// create row with squids
	case crab: createCrabRow(level, yPos, buffer); break;	// create row with crabs
	case octopus: createOctopusRow(level, yPos, buffer); break;	// create row with octopuses
	}

	return buffer;
}

void Enemies::createSquidRow(int level, float yPos, list<Enemy*>& buffer) {

	float xPos = 20.f;

	for (int i = level % 10 + 4; i > 0; i--) {

		buffer.push_back(new Squid(textures["squid1"], textures["squid2"], xPos, yPos)); // push back new squid
		xPos += 70.f;	 // set new x position for next element
	}
}

void Enemies::createCrabRow(int level, float yPos, list<Enemy*>& buffer) {

	float xPos = 20.f;

	for (int i = level % 10 + 4; i > 0; i--) {

		buffer.push_back(new Crab(textures["crab1"], textures["crab2"], xPos, yPos)); // push back new crab
		xPos += 70.f;	 // set new x position for next element
	}
}

void Enemies::createOctopusRow(int level, float yPos, list<Enemy*>& buffer) {

	float xPos = 20.f;

	for (int i = level % 10 + 4; i > 0; i--) {

		buffer.push_back(new Octopus(textures["octopus1"], textures["octopus2"], xPos, yPos)); // push back new octopus
		xPos += 70.f;	 // set new x position for next element
	}
}

int Enemies::additionalRow(int level, enemyType type) {

	// getting tens part of level
	level = (level - (level / 100) * 100) / 10;

	switch (type) {

	case crab:

		if (level % 3 == 2) return 1;
		else return 0;
		break;

	case octopus:

		if (level % 3) return 1;
		else return 0;
		break;
	}

	return 0;
}

void Enemies::render(sf::RenderWindow* window) {

	for (mainListIt i = mainList.begin(); i != mainList.end(); i++) {	// iteration over the main list

		for (listIt j = (*i).begin(); j != (*i).end(); j++) (*j)->render(window);	// render all enemies from list
	}

	bullets->renderBullets(window);
}

void Enemies::updateGroupState(bool& isGameEnded, float deltaTime) {

	mainListIt mainEnd = mainList.end();

	for (mainListIt i = mainList.begin(); i != mainEnd; i++) {	// iteration over the main list

		listIt end = (*i).end();

		for (listIt j = (*i).begin(); j != end; j++) {	// update state of all enemies from list

			if ((*j)->checkBottomBorderCollision()) isGameEnded = true;
			(*j)->update(deltaTime, leftDirection);
			spawnBullet(*j);
		}
	}
}

void Enemies::borderCollisionsCheck() {

	if (!mainList.empty()) {

		if (leftDirection) leftBorderCollisionsCheck();
		else rightBorderCollisionsCheck();
	}
}

void Enemies::leftBorderCollisionsCheck() {

	for (mainListIt i = mainList.begin(); i != mainList.end(); i++) {

		if (!(*i).empty()) {

			if ((*((*i).begin()))->checkSideBorderCollision(leftDirection)) {

				moveToLowerRows();	// move all enemies to lover rows if enemy is on screen border
				leftDirection = false;
				break;
			}
		}
	}
}

void Enemies::rightBorderCollisionsCheck() {

	for (mainListIt i = mainList.begin(); i != mainList.end(); i++) {

		if (!(*i).empty()) {

			if ((*(--(*i).end()))->checkSideBorderCollision(leftDirection)) {

				moveToLowerRows();		// move all enemies to lover rows if enemy is on screen border
				leftDirection = true;
				break;
			}
		}
	}
}

void Enemies::moveToLowerRows() {

	mainListIt mainEnd = mainList.end();

	for (mainListIt i = mainList.begin(); i != mainEnd; i++) {	// iteration over the main list

		listIt end = (*i).end();

		for (listIt j = (*i).begin(); j != end; j++) (*j)->moveToLowerRow();	// move all enemies to lover rows
	}
}

list<list<Enemy*>>& Enemies::getEnemyList() {

	return mainList;
}

vector<EnemyBullet>& Enemies::getBulletsVector() {

	return bullets->getBulletsVector();
}

void Enemies::deleteAllEnemiesAndBullets() {	// iteration over the main list

	for (mainListIt i = mainList.begin(); i != mainList.end(); i++) {

		for (listIt j = (*i).begin(); j != (*i).end(); j++) delete* j;	// delete enemy
	}

	for (mainListIt i = mainList.begin(); i != mainList.end(); i++) (*i).clear();	// clear list

	mainList.clear();	// clear main list

	bullets->deleteAllEnemyBullets();	// delete all enemy bullets

	level = -1;	// set first level
}
