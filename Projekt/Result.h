#pragma once

/*@author Michal Pawlowski*/
/*@file Result.h*/

#include <iostream>
#include <fstream>

using namespace std;

#ifndef RESULT_H
#define RESULT_H

/** Declaration of Result class
@author Michal Pawlowski
@date 2021-05-11
*/
class Result {

	/** score */
	int score = 0;
	/** best score */
	int bestScore = 0;
	/** level */
	int level = 0;

	/** load best score from file */
	void loadBestScore();
	/** set best score */
	void saveBestScore();

public:

	/** constructor */
	Result();
	/** destructor */
	~Result();
	/** give acces to score */
	int& getScore();
	/** give acces to best score */
	int& getBestScore();
	/** give acces to level */
	int& getLevel();
	/** reset score */
	void resetScore();
	/** reset level */
	void resetLevel();
	/** update new best score */
	void updateBestScore();
};

#endif