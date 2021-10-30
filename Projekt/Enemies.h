#pragma once

/*@author Michal Pawlowski*/
/*@file Enemies.h*/

#include <list>
#include <map>
#include <SFML/Graphics.hpp>
#include "Squid.h"
#include "Crab.h"
#include "Octopus.h"
#include "EnemyBullets.h"
#include "PlayerBullets.h"

#ifndef ENEMIES_H
#define ENEMIES_H

using namespace std;

typedef list<list<Enemy*>>::iterator mainListIt;
typedef list<Enemy*>::iterator listIt;

/** Declaration of Group class
@author Michal Pawlowski
@date 2021-05-11
*/

class Enemies {

	/** level, number of wave */
	int level;
	/** defines direction of group */
	bool leftDirection;
	/** list of enemies */
	list<list<Enemy*>> mainList;
	/** map of textures */
	map<string, sf::Texture*> textures;
	/** enemy bullets */
	EnemyBullets* bullets;

	/** spawn enemy bullet */
	void spawnBullet(Enemy* enemy);
	/** creates new wave of enemy */
	void createWave();
	/** creates sector with one type enemy */
	void createSector(enemyType type, float& yPos);
	/** creates one row of enemy */
	list<Enemy*> createRow(int level, enemyType type, float yPos);
	/** creates one row of squids */
	void createSquidRow(int level, float yPos, list<Enemy*>& buffer);
	/** creates one row of crabs */
	void createCrabRow(int level, float yPos, list<Enemy*>& buffer);
	/** creates one row of octopuses */
	void createOctopusRow(int level, float yPos, list<Enemy*>& buffer);
	/** calculate is additional row id needed */
	int additionalRow(int level, enemyType type);
	/** updates positon of all enemies from group */
	void updateGroupState(bool& isGameEnded, float deltaTime);
	/** checks if any enemy collide with window borderline */
	void borderCollisionsCheck();
	/** checks if any enemy collide with left window borderline */
	void leftBorderCollisionsCheck();
	/** checks if any enemy collide with right window borderline */
	void rightBorderCollisionsCheck();
	/** moves all group to lower rows */
	void moveToLowerRows();

public:

	/** construcor */
	Enemies(sf::Texture* octopus1, sf::Texture* octopus2, sf::Texture* crab1, sf::Texture* crab2, sf::Texture* squid1, sf::Texture* squid2, sf::Texture* enemyBullet);
	/** destrucor */
	~Enemies();
	/** update events */
	void update(int& level, bool& isGameEnded, PlayerBullets& playerBullets, float deltaTime);
	/** draws all enemies from group */
	void render(sf::RenderWindow* window);
	/** give access to list of enemies */
	list<list<Enemy*>>& getEnemyList();
	/** give access to bullets vector */
	vector<EnemyBullet>& getBulletsVector();
	/** delete all enemies and their bullets */
	void deleteAllEnemiesAndBullets();
};

#endif


