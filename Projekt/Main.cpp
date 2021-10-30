/*@author Michal Pawlowski*/
/*@file Main.h*/

#include "Game.h"

int main() {
	{

		// Initialize game engine
		Game game;

		// Game loop
		while (game.isWindowOpened()) {

			// Update game state
			game.update();
			// Render current state
			game.render();
		}
	}
	return 0;
}