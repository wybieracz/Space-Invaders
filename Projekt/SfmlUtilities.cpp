/*@author Michal Pawlowski*/
/*@file SfmlUtilities.cpp*/

#include "SfmlUtilities.h"

#define FPS_LIMIT 120

SfmlUtilities::SfmlUtilities() : window(nullptr) {

	initializeWindow();
	initializeIcon();
}

SfmlUtilities::~SfmlUtilities() {

	window->close();
	delete window;
}

void SfmlUtilities::initializeWindow() {

	videoMode.height = 1080;	// sets window size
	videoMode.width = 1920;

	window = new sf::RenderWindow(videoMode, "Space Invaders", sf::Style::Fullscreen);	// create new RenderWindow and set window title and fullscreen mode

	window->setFramerateLimit(FPS_LIMIT);	// sets fps limit
	window->setVerticalSyncEnabled(false);	// disable v-sync
}

void SfmlUtilities::initializeIcon() {

	try {

		if (!icon.loadFromFile("Textures/Icon_1.png")) throw 1;	//load program icon
	}
	catch (int errorNumber) {

		if (errorNumber == 1) {

			std::cerr << "ERROR[1]: Unable to open game icon." << std::endl;	// error message if unable to open file
			exit(errorNumber);
		}
	}

	(*window).setIcon(32, 26, icon.getPixelsPtr());
}

void SfmlUtilities::inputCheck(bool& isGameStarted, bool& isGameEnded, bool& isNewGameStarted) {

	while (window->pollEvent(sfmlEvent)) {

		if (sfmlEvent.key.code == sf::Keyboard::Escape) {	// close game

			window->close();
		}

		if (sfmlEvent.key.code == sf::Keyboard::Enter) {	// start game

			if (!isGameStarted && !isGameEnded) isGameStarted = true;
			if (isGameStarted && isGameEnded) isNewGameStarted = true;
		}
			
	}
}

sf::RenderWindow* SfmlUtilities::getWindow() {

	return window;
}

sf::Event& SfmlUtilities::getEvent() {

	return sfmlEvent;
}

const bool SfmlUtilities::isWindowOpened() const {

	return window->isOpen();
}
