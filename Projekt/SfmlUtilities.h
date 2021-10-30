#pragma once

/*@author Michal Pawlowski*/
/*@file SfmlUtilities.h*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifndef SFML_H
#define SFML_H

/** Declaration of SfmlUtiliteis class
@author Michal Pawlowski
@date 2021-05-11
*/
class SfmlUtilities {

	/** defines a video mode */
	sf::VideoMode videoMode;
	/** load and manipulate program icon */
	sf::Image icon;
	/** serve as a target for 2D drawing */
	sf::RenderWindow* window;
	/** defines a system event */
	sf::Event sfmlEvent;

	/** initialize program window */
	void initializeWindow();
	/** initialize program icon */
	void initializeIcon();

public:

	/** no argument constructor */
	SfmlUtilities();
	/** destructor */
	~SfmlUtilities();
	/** checks input */
	void inputCheck(bool& isGameStarted, bool& isGameEnded, bool& isNewGameStarted);
	/** give acceess to window */
	sf::RenderWindow* getWindow();
	/** give acceess to event */
	sf::Event& getEvent();
	/** return information is program window open */
	const bool isWindowOpened() const;
};

#endif