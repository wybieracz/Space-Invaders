#pragma once

/*@author Michal Pawlowski*/
/*@file Collisions.h*/

#include <SFML/System.hpp>
#include "Walls.h"
#include "Player.h"
#include "Ufo.h"
#include "Enemies.h"

#ifndef COLLISIONS_H
#define COLLISIONS_H

/** Declaration of Collisions class
@author Michal Pawlowski
@date 2021-05-11
*/
class Collision {

	/** collision sound */
	sf::Sound explosionSound;

	/** check collisions beetween enemies and player's bullets */
	void checkCollisionsBulletsEnemies(int& score, vector<PlayerBullet>& bullets, list<list<Enemy*>>& mainList);
	/** check collisions beetween enemy and player's bullets */
	void checkCollisionsBulletsEnemy(int& score, vector<PlayerBullet>& bullets, list<Enemy*>& list, bool& isDeletion);
	/** check collision beetween enemy and single bullet */
	bool checkCollisionBulletEnemy(const PlayerBullet& bullet, Enemy* enemy);

	/** check collision beetween walls and player bullets or enemy bullets */
	template<typename Bullets>
	void checkCollisionWallsBullets(vector<Bullets>& bullets, Walls& wallsParam);
	/** check collision beetween single wall and player bullets or enemy bullets */
	template<typename Bullets>
	void checkCollisionWallBullets(vector<Bullets>& bullets, map<string, sf::Texture*>& textures, vector<Block>& wall, bool& isDeletion);

	/** check collision beetween single wall and single player bullet */
	bool checkCollisionWallBullet(const PlayerBullet& bullet, const Block& wall);
	/** calculates collision between triangle wall and player bullet */
	bool checkCollisionTriangleWallBullet(const PlayerBullet& bullet, const Block& wall);

	/** check collision between 11th block of wall and player bullet */
	bool checkCollision11thBlockBullet(const PlayerBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of player bullet */
	bool checkCollision11thBlockBulletLeftVertex(const PlayerBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of player bullet */
	bool checkCollision11thBlockBulletRightVertex(const PlayerBullet& bullet, const Block& wall);
	/** check collision between 13th block of wall and player bullet */
	bool checkCollision13thBlockBullet(const PlayerBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of player bullet */
	bool checkCollision13thBlockBulletLeftVertex(const PlayerBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of player bullet */
	bool checkCollision13thBlockBulletRightVertex(const PlayerBullet& bullet, const Block& wall);

	/** check collision beetween single wall and single enemy bullet */
	bool checkCollisionWallBullet(const EnemyBullet& bullet, const Block& wall);
	/** calculates collision between triangle wall and enemy bullet */
	bool checkCollisionTriangleWallBullet(const EnemyBullet& bullet, const Block& wall);

	/** check collision between 11th block of wall and enemy bullet */
	bool checkCollision0thBlockBullet(const EnemyBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of enemy bullet */
	bool checkCollision0thBlockBulletLeftVertex(const EnemyBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of enemy bullet */
	bool checkCollision0thBlockBulletRightVertex(const EnemyBullet& bullet, const Block& wall);
	/** check collision between 13th block of wall and enemy bullet */
	bool checkCollision4thBlockBullet(const EnemyBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of enemy bullet */
	bool checkCollision4thBlockBulletLeftVertex(const EnemyBullet& bullet, const Block& wall);
	/** check collision between 11th block of wall and left vertex of enemy bullet */
	bool checkCollision4thBlockBulletRightVertex(const EnemyBullet& bullet, const Block& wall);

	/** give information is bullet vertex beetween block vertices on x axis*/
	template<typename Bullet>
	bool isBulletVertexBetweenBlockVertices(const Bullet& bullet, const Block& wall, bool left);
	/** calculates small triangle surface */
	float getSmallTriangleSurface(float Xa, float Ya, float Xb, float Yb, float Xc, float Yc);
	/** deal demage to block */
	void dealDamage(map<string, sf::Texture*>& textures, vector<Block>& wall, blockVectorIt& j, bool& isDeletion);
	/** update score */
	void addPoints(int& score, Enemy* enemy);

	/** check collisions beetween player and enemy bullets */
	void checkCollisionPlayerEnemyBullet(Player& player, vector<EnemyBullet>& enemyBullets, bool& isGameEnded);
	/** check collision between player bullets and enemy bullets */
	void chechCollisionPlayerBulletsEnemyBullets(vector<PlayerBullet>& playerBullets, vector<EnemyBullet>& enemyBullets);
	/** check collision between player bullets and ufo */
	void checkCollisionPlayerBulletsUfo(int& score, Player& player, vector<PlayerBullet>& playerBullets, Ufo& ufo);

public:

	/** constructor */
	Collision(sf::SoundBuffer* explsionSoundParam);
	/** check all possible collisions */
	void checkCollisions(int& score, bool& isGameEnded, Player& player, Ufo& ufo, vector<PlayerBullet>& bullets, vector<EnemyBullet>&enemyBullets, list<list<Enemy*>>& mainList, Walls& wallsParam);

};

#endif
