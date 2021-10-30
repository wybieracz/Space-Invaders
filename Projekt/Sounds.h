#pragma once

/*@author Michal Pawlowski*/
/*@file Sounds.h*/

#include <map>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#ifndef SOUNDS_H
#define SOUNDS_H

using namespace std;

/** Declaration of sounds class
@author Michal Pawlowski
@date 2021-05-11
*/
class Sounds {

	/** main theme music */
	sf::Sound music;
	/** player death sound */
	sf::Sound gameOverSound;
	/** map which include all textures */
	map<string, sf::SoundBuffer*> sounds;

	/** open files with sounds */
	void openSoundFile(const string name, const string fileName);
	/** initialize main theme music */
	void initializeMusic();
	/** initialize player death sound */
	void initializeGameOverSound();

public:

	/** constructor */
	Sounds();
	/** destructor */
	~Sounds();
	/** give access to texture pointer */
	sf::SoundBuffer* getSoundBuffer(string key);
	/** stop music */
	void stopMusic();
	/** start music */
	void playMusic();
	/** play game over sound */
	void playGameOverSound();
	/** stop game over sound */
	void stopGameOverSound();
};

#endif