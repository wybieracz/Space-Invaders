/*@author Michal Pawlowski*/
/*@file Collision.cpp*/

#include "Collisions.h"

#define TRIANGLE_BLOCK_SURFACE 450.f // 30.f * 30.f / 2
#define COLLISION_ACCURACY 6	// define accuracy of triangle wall & bullet collision check

Collision::Collision(sf::SoundBuffer* explsionSoundParam) {

	explosionSound.setBuffer(*explsionSoundParam);
	explosionSound.setVolume(20.f);
}

void Collision::checkCollisions(int& score, bool& isGameEnded, Player& player, Ufo& ufo, vector<PlayerBullet>& bullets, vector<EnemyBullet>& enemyBullets, list<list<Enemy*>>& mainList, Walls& wallsParam) {

	checkCollisionsBulletsEnemies(score, bullets, mainList);
	checkCollisionWallsBullets(bullets, wallsParam);
	checkCollisionWallsBullets(enemyBullets, wallsParam);
	checkCollisionPlayerEnemyBullet(player, enemyBullets, isGameEnded);
	chechCollisionPlayerBulletsEnemyBullets(bullets, enemyBullets);
	checkCollisionPlayerBulletsUfo(score, player, bullets, ufo);
}

void Collision::checkCollisionsBulletsEnemies(int& score,vector<PlayerBullet>& bullets, list<list<Enemy*>>& mainList) {

	bool isDeletion = false;

	for (mainListIt i = mainList.begin(); i != mainList.end(); ) {

		if ((*i).empty()) i = mainList.erase(i);	// delete list if empty
		else {

			checkCollisionsBulletsEnemy(score, bullets, (*i), isDeletion);	// check collision beetween row of enemy and bullets
			++i;
		}
		
	}
}

void Collision::checkCollisionsBulletsEnemy(int& score, vector<PlayerBullet>& bullets, list<Enemy*>& list, bool& isDeletion) {

	for (listIt j = list.begin(); j != list.end(); ) {

		isDeletion = false;

		for (playerBulletIt k = bullets.begin(); k != bullets.end(); k++) {

			if (checkCollisionBulletEnemy((*k), (*j))) {	// check collision beetween bullet and enemy

				explosionSound.play();	// play sound if collision
				bullets.erase(k);	// delete bullet if collision

				addPoints(score, *j);	// add points if collision
				delete (*j);	// delete enemy if collision
				j = list.erase(j);	// delete element of list if collision

				isDeletion = true;
				break;
			}
		}
		if (!isDeletion)j++;
	}
}

bool Collision::checkCollisionBulletEnemy(const PlayerBullet& bullet, Enemy* enemy) {

	if (bullet.getBounds().intersects(enemy->getBounds())) return true; // check collision beetween bullet and enemy
	else return false;
}

template<typename Bullets>
void Collision::checkCollisionWallsBullets(vector<Bullets>& bullets, Walls& wallsParam) {

	bool isDeletion = false;

	for (wallVectorIt i = wallsParam.getWalls().begin(); i != wallsParam.getWalls().end(); ) {

		if ((*i).getWall().empty()) i = wallsParam.getWalls().erase(i);
		else {

			checkCollisionWallBullets(bullets, wallsParam.getTextures(), (*i).getWall(), isDeletion); // check collision beetween bullets and wall
			++i;
		}
	}
}

template<typename Bullets>
void Collision::checkCollisionWallBullets(vector<Bullets>& bullets, map<string, sf::Texture*>& textures, vector<Block>& wall, bool& isDeletion) {

	for (blockVectorIt j = wall.begin(); j != wall.end(); ) {	// interation over the wall segments

		isDeletion = false;

		for (auto k = bullets.begin(); k != bullets.end(); k++) {	// iteration over the bullets

			if (checkCollisionWallBullet((*k), (*j))) {

				bullets.erase(k);	// delete bullet if collision
				dealDamage(textures, wall, j, isDeletion);	// deal damage to wall if collision
				break;
			}
		}
		if (!isDeletion)++j;
	}
}

bool Collision::checkCollisionWallBullet(const PlayerBullet& bullet, const Block& wall) {

	if (!wall.getIsSquare() && (wall.getSpriteRotation() == 180.f || wall.getSpriteRotation() == 270.f)) {
		
		if (checkCollisionTriangleWallBullet(bullet, wall)) return true;	// check collsion for triangle wall
		else return false;
	}
	else {

		if (wall.getBounds().intersects(bullet.getBounds())) return true;	// check collsion for square wall
		else return false;
	}
}

bool Collision::checkCollisionTriangleWallBullet(const PlayerBullet& bullet, const Block& wall) {

	if (wall.getSpriteRotation() == 180.f) return checkCollision11thBlockBullet(bullet, wall); // check collsion for 11th block of wall
	else return checkCollision13thBlockBullet(bullet, wall);	// check collsion for 13th block of wall
	
	return false;
}

bool Collision::checkCollision11thBlockBullet(const PlayerBullet& bullet, const Block& wall) {
	
	if (checkCollision11thBlockBulletLeftVertex(bullet, wall)) return true;	// check collsion for 11th block of wall using left vertex of bullet
	if (checkCollision11thBlockBulletRightVertex(bullet, wall)) return true;	// check collsion for 11th block of wall using right vertex of bullet

	return false;
}

bool Collision::checkCollision11thBlockBulletLeftVertex(const PlayerBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top + wall.getBounds().height,
			wall.getBounds().left + wall.getBounds().width, wall.getBounds().top, bullet.getBounds().left, bullet.getBounds().top)) return true;
	}
	return false;
}

bool Collision::checkCollision11thBlockBulletRightVertex(const PlayerBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, false)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top + wall.getBounds().height,
			wall.getBounds().left + wall.getBounds().width, wall.getBounds().top, bullet.getBounds().left + bullet.getBounds().width, bullet.getBounds().top)) return true;
	}
	return false;
}

bool Collision::checkCollision13thBlockBullet(const PlayerBullet& bullet, const Block& wall) {

	if (checkCollision13thBlockBulletLeftVertex(bullet, wall)) return true;	// check collsion for 13th block of wall using left vertex of bullet
	if (checkCollision13thBlockBulletRightVertex(bullet, wall)) return true;	// check collsion for 13th block of wall using right vertex of bullet

	return false;
}

bool Collision::checkCollision13thBlockBulletLeftVertex(const PlayerBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top, wall.getBounds().left + wall.getBounds().width,
			wall.getBounds().top + wall.getBounds().height, bullet.getBounds().left, bullet.getBounds().top)) return true;
	}
	return false;
}

bool Collision::checkCollision13thBlockBulletRightVertex(const PlayerBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top, wall.getBounds().left + wall.getBounds().width,
			wall.getBounds().top + wall.getBounds().height, bullet.getBounds().left + bullet.getBounds().width, bullet.getBounds().top)) return true;
	}
	return false;
}

bool Collision::checkCollisionWallBullet(const EnemyBullet& bullet, const Block& wall) {

	if (!wall.getIsSquare() && (wall.getSpriteRotation() == 0.f || wall.getSpriteRotation() == 90.f)) {

		if (checkCollisionTriangleWallBullet(bullet, wall)) return true;	// check collsion for triangle wall
		else return false;
	}
	else {

		if (wall.getBounds().intersects(bullet.getBounds())) return true;	// check collsion for square wall
		else return false;
	}
}

bool Collision::checkCollisionTriangleWallBullet(const EnemyBullet& bullet, const Block& wall) {

	if (wall.getSpriteRotation() == 0.f) return checkCollision0thBlockBullet(bullet, wall);	// check collsion for 0th block of wall
	else return checkCollision4thBlockBullet(bullet, wall);	// check collsion for 4th block of wall

	return false;
}

bool Collision::checkCollision0thBlockBullet(const EnemyBullet& bullet, const Block& wall) {

	if (checkCollision0thBlockBulletLeftVertex(bullet, wall)) return true;	// check collsion for 0th block of wall using left vertex of bullet
	if (checkCollision0thBlockBulletRightVertex(bullet, wall)) return true;	// check collsion for 0th block of wall using right vertex of bullet

	return false;
}

bool Collision::checkCollision0thBlockBulletLeftVertex(const EnemyBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top + wall.getBounds().height,
			wall.getBounds().left + wall.getBounds().width, wall.getBounds().top, bullet.getBounds().left, bullet.getBounds().top + bullet.getBounds().height)) return true;
	}
	return false;
}

bool Collision::checkCollision0thBlockBulletRightVertex(const EnemyBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, false)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top + wall.getBounds().height,
			wall.getBounds().left + wall.getBounds().width, wall.getBounds().top, bullet.getBounds().left + bullet.getBounds().width, bullet.getBounds().top + bullet.getBounds().height)) return true;
	}
	return false;
}

bool Collision::checkCollision4thBlockBullet(const EnemyBullet& bullet, const Block& wall) {

	if (checkCollision4thBlockBulletLeftVertex(bullet, wall)) return true;	// check collsion for 4th block of wall using left vertex of bullet
	if (checkCollision4thBlockBulletRightVertex(bullet, wall)) return true;	// check collsion for 4th block of wall using left vertex of bullet

	return false;
}

bool Collision::checkCollision4thBlockBulletLeftVertex(const EnemyBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top, wall.getBounds().left + wall.getBounds().width,
			wall.getBounds().top + wall.getBounds().height, bullet.getBounds().left, bullet.getBounds().top + bullet.getBounds().height)) return true;
	}
	return false;
}

bool Collision::checkCollision4thBlockBulletRightVertex(const EnemyBullet& bullet, const Block& wall) {

	// return true if surface of triangle (2 vertex of wall block and 1 vertex of bullet) is less than surface of triangle block of wall divided by COLLISION_ACCURACY

	if (isBulletVertexBetweenBlockVertices(bullet, wall, true)) {	// check if bullet vertex is between wall wertex on X axis

		if (TRIANGLE_BLOCK_SURFACE > COLLISION_ACCURACY* getSmallTriangleSurface(wall.getBounds().left, wall.getBounds().top, wall.getBounds().left + wall.getBounds().width,
			wall.getBounds().top + wall.getBounds().height, bullet.getBounds().left + bullet.getBounds().width, bullet.getBounds().top + bullet.getBounds().height)) return true;
	}
	return false;
}

template<typename Bullet>
bool Collision::isBulletVertexBetweenBlockVertices(const Bullet& bullet, const Block& wall, bool left) {	// check if bullet vertex is between wall wertex on X axis

	if (left) if ((wall.getBounds().left < bullet.getBounds().left) && (bullet.getBounds().left < wall.getBounds().left + wall.getBounds().width)) return true;
	else if ((wall.getBounds().left < bullet.getBounds().left + bullet.getBounds().width) && (bullet.getBounds().left + bullet.getBounds().width < wall.getBounds().left + wall.getBounds().width)) return true;

	return false;
}

float Collision::getSmallTriangleSurface(float Xa, float Ya, float Xb, float Yb, float Xc, float Yc) {

	// calculate triangle surface

	return (abs((Xb - Xa) * (Yc - Ya) - (Yb - Ya) * (Xc - Xa))) / 2;
}

void Collision::dealDamage(map<string, sf::Texture*>& textures, vector<Block>& wall, blockVectorIt& j, bool& isDeletion) {	// set new texture for wall block

	if ((*j).getIsSquare()) {
		switch (++(*j).getStageAccess()) {

		case 2: (*j).setNewTexture(textures["square2"]); break;
		case 3: (*j).setNewTexture(textures["square3"]); break;
		case 4: (*j).setNewTexture(textures["square4"]); break;
		default: 
			j = wall.erase(j);	// delete block if destroyed
			isDeletion = true;
			break;
		}
	}
	else {
		switch (++(*j).getStageAccess()) {

		case 2: (*j).setNewTexture(textures["triangle2"]); break;
		case 3: (*j).setNewTexture(textures["triangle3"]); break;
		case 4: (*j).setNewTexture(textures["triangle4"]); break;
		default:
			j = wall.erase(j);	// delete block if destroyed
			isDeletion = true;
			break;
		}
	}
}

void Collision::addPoints(int& score, Enemy* enemy) {	// add point depending on type of enemy
	
	switch ((*enemy).getEnemyType()) {

	case squid: score += 30; break;
	case crab: score += 20; break;
	case octopus: score += 10; break;
	}
}

void Collision::checkCollisionPlayerEnemyBullet(Player& player, vector<EnemyBullet>& enemyBullets, bool& isGameEnded) {

	for (enemyBulletIt i = enemyBullets.begin(); i != enemyBullets.end(); ) {	// iterate over the enemy bullets

		if ((*i).getBounds().intersects(player.getBounds())) {

			i = enemyBullets.erase(i);	// delete bullet if collision
			player.decreaseHealth();	// decrease player health if collision
			if (!player.getHealth()) isGameEnded = true;	// end game if player health equal 0
		}
		else ++i;
	}
}

void Collision::chechCollisionPlayerBulletsEnemyBullets(vector<PlayerBullet>& playerBullets, vector<EnemyBullet>& enemyBullets) {

	bool isDeletion = false;

	for (enemyBulletIt i = enemyBullets.begin(); i != enemyBullets.end(); ) {	// iterate over the enemy bullets

		isDeletion = false;

		for (playerBulletIt j = playerBullets.begin(); j != playerBullets.end(); ) {	// iterate over the player bullets

			if ((*i).getBounds().intersects((*j).getBounds())) {

				i = enemyBullets.erase(i);	// delete bullets if collision
				playerBullets.erase(j);
				isDeletion = true;
				break;
			}
			else ++j;
		}
		if (!isDeletion) ++i;
	}
}

void Collision::checkCollisionPlayerBulletsUfo(int& score, Player& player, vector<PlayerBullet>& playerBullets, Ufo& ufo) {

	for (playerBulletIt i = playerBullets.begin(); i != playerBullets.end(); ) {	// iterate over the player bullets

		if (ufo.getBounds().intersects((*i).getBounds())) {

			explosionSound.play();	// play sound if collision
			playerBullets.erase(i);	// delete bullet if collision
			ufo.reset();	// reset ufo if collision
			score += 150;	// add points if collision
			player.increaseHealth();	// increment player health
			break;
		}
		else ++i;
	}
}
