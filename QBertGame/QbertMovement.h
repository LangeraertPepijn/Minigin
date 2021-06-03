#pragma once
#include <SDL_scancode.h>
#include "InputManager.h"

struct QBertMovement
{
	SDL_Scancode LeftDownKeyboard = SDL_SCANCODE_KP_1;
	SDL_Scancode RightDownKeyboard = SDL_SCANCODE_KP_3;
	SDL_Scancode LeftUpKeyboard = SDL_SCANCODE_KP_7;
	SDL_Scancode RightUpKeyboard = SDL_SCANCODE_KP_9;

	ControllerButton LeftDownGamepad = ControllerButton::ButtonDDown;
	ControllerButton RightDownGamepad = ControllerButton::ButtonDRight;
	ControllerButton LeftUpKeyGamepad = ControllerButton::ButtonDLeft;
	ControllerButton RightUpGamepad = ControllerButton::ButtonDUp;
};
