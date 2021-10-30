/*@author Michal Pawlowski*/
/*@file PlayerBullets.cpp*/

#include "PlayerBullets.h"

PlayerBullets::PlayerBullets(sf::SoundBuffer* shootSoundParam) {

	shootSound.setBuffer(*shootSoundParam);
	shootSound.setVolume(20.f);
}

PlayerBullets::~PlayerBullets() {

	deleteAllBullets();
}

void PlayerBullets::updateBullets(float deltaTime) {

	for (playerBulletIt i = bullets.begin(); i != bullets.end(); ) {

		(*i).update(deltaTime);

		// Check if bullet is out the screen
		if ((*i).getBounds().top + 15.f < 0.f) {

			// Delete bullet
			i = bullets.erase(i);
		}
		else ++i;
	}
}

void PlayerBullets::spawnBullet(float xPos) {

	bullets.push_back(PlayerBullet(xPos + 24.f, 1035.f, 0.f, -1.f));	// push back new bullet
	shootSound.play();	// play shooting sound
}

void PlayerBullets::renderBullets(sf::RenderWindow* windowPtr) const {

	for (const auto& i : bullets) i.render(windowPtr);	// render bullets
}

vector<PlayerBullet>& PlayerBullets::getBulletsVector() {

	return bullets;
}

void PlayerBullets::deleteAllBullets() {

	bullets.clear();
}
