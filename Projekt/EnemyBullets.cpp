/*@author Michal Pawlowski*/
/*@file EnemyBullets.cpp*/

#include "EnemyBullets.h"

EnemyBullets::EnemyBullets(sf::Texture* texture) : bulletTexture(texture) {}

EnemyBullets::~EnemyBullets() {

	deleteAllEnemyBullets();
}

void EnemyBullets::updateBullets(float deltaTime) {

	for (enemyBulletIt i = bullets.begin(); i != bullets.end(); ) {

		(*i).update(deltaTime);

		// Check if bullet is out the screen
		if ((*i).getBounds().top > 1080.f) {

			// Delete bullet
			i = bullets.erase(i);
		}
		else ++i;
	}
}

void EnemyBullets::spawnBullet(float xPos, float yPos) {

	bullets.push_back(EnemyBullet(xPos + 22.f, yPos + 32, 0.f, 1.f, bulletTexture));
}

void EnemyBullets::renderBullets(sf::RenderWindow* windowPtr) const {

	for (const auto& i : bullets) i.render(windowPtr);	// render enemy bullets
}

vector<EnemyBullet>& EnemyBullets::getBulletsVector() {

	return bullets;
}

void EnemyBullets::deleteAllEnemyBullets() {

	bullets.clear();
}
