/*@author Michal Pawlowski*/
/*@file Sounds.cpp*/

#include "Sounds.h"

void Sounds::openSoundFile(const string name, const string fileName) {

	sounds[name] = new sf::SoundBuffer(); 	// create new empty texture

	try {

		if (!sounds[name]->loadFromFile(fileName)) throw 4;		// load texture from file
	}
	catch (int errorNumber) {

		if (errorNumber == 4) {

			std::cerr << "ERROR[4]: Unable to open sound file." << std::endl;	// error message if unable to open file
			exit(errorNumber);
		}
	}
}

void Sounds::initializeMusic() {

	music.setBuffer(*sounds["main_theme"]);
	music.setVolume(50.f);
	music.setLoop(true);
	music.play();
}

void Sounds::initializeGameOverSound() {

	gameOverSound.setBuffer(*sounds["game_over"]);
	gameOverSound.setVolume(30.f);
}

Sounds::Sounds() {

	openSoundFile("main_theme", "Sounds/main_theme.ogg");
	openSoundFile("ufo_lowpitch", "Sounds/ufo_lowpitch.ogg");
	openSoundFile("shoot", "Sounds/shoot.wav");
	openSoundFile("explosion", "Sounds/explosion.ogg");
	openSoundFile("game_over", "Sounds/game_over.ogg");
	initializeMusic();
	initializeGameOverSound();
}

Sounds::~Sounds() {

	music.stop();	//	stop music

	// removing sounds from buffer
	for (auto& i : sounds) delete i.second;
	sounds.clear();
}

sf::SoundBuffer* Sounds::getSoundBuffer(string key) {

	return sounds[key];
}

void Sounds::stopMusic() {

	if (music.getStatus() == sf::SoundSource::Playing) music.stop();
}

void Sounds::playMusic() {

	music.play();
}

void Sounds::playGameOverSound() {

	gameOverSound.play();
}

void Sounds::stopGameOverSound() {

	gameOverSound.stop();
}
