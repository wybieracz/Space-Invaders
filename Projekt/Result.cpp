/*@author Michal Pawlowski*/
/*@file Result.cpp*/

#include "Result.h"

void Result::loadBestScore() {

	ifstream file;
	file.open("data.si");
	
	if (file.is_open()) file >> bestScore;	// load best score from file

	file.close();
}

void Result::saveBestScore() {

	ofstream file;
	file.open("data.si");
	file << bestScore;	// save best score to file
	file.close();
}

Result::Result() {

	loadBestScore();
}

Result::~Result() {

	saveBestScore();
}

int& Result::getScore() {

	return score;
}

int& Result::getBestScore() {
	
	return bestScore;
}

int& Result::getLevel() {

	return level;
}

void Result::resetScore() {

	score = 0;
}

void Result::resetLevel() {

	level = 0;
}

void Result::updateBestScore() {

	if (bestScore < score) bestScore = score;
}
