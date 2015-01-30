//
//  InputManager.cpp
//  Sedimental Storm
//
//  Created by Max Savage on 1/22/15.
//  Copyright (c) 2015 Max Savage. All rights reserved.
//

#include "InputManager.h"


InputManager::InputManager()
{
}

//Acquire Joysticks
void InputManager::FindJoystick()
{
	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);

	//If joystick is plugged in, get capabilities
	if (sf::Joystick::isConnected(0)){
		//Get number of buttons
		unsigned int buttons = sf::Joystick::getButtonCount(0);
	}

}





/* Profile: Xbox 360 Controller
sf::Joystick::isButtonPressed(0, 0) //A Button
sf::Joystick::isButtonPressed(0, 1) //B Button
sf::Joystick::isButtonPressed(0, 2) //X Button
sf::Joystick::isButtonPressed(0, 3) //Y Button

if (sf::Joystick::isButtonPressed (0, A))
if (sf::Joystick::isButtonPressed (0, B))
if (sf::Joystick::isButtonPressed (0, X))
if (sf::Joystick::isButtonPressed (0, Y))

*/