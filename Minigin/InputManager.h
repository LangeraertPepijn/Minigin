#pragma once
#include <Windows.h>
#include <windef.h>
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include "Command.h"
#include <SDL.h>

enum class ControllerButton
{
	ButtonA = XINPUT_GAMEPAD_A,
	ButtonB = XINPUT_GAMEPAD_B,
	ButtonX = XINPUT_GAMEPAD_X,
	ButtonY = XINPUT_GAMEPAD_Y,

	ButtonLB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	ButtonRB = XINPUT_GAMEPAD_RIGHT_SHOULDER,

	ButtonDDown = XINPUT_GAMEPAD_DPAD_DOWN,
	ButtonDUp = XINPUT_GAMEPAD_DPAD_UP,
	ButtonDRight = XINPUT_GAMEPAD_DPAD_RIGHT,
	ButtonDLeft = XINPUT_GAMEPAD_DPAD_LEFT,

	ButtonTLeft = XINPUT_GAMEPAD_LEFT_THUMB,
	ButtonTRight = XINPUT_GAMEPAD_RIGHT_THUMB,

};
enum class ExecuteType
{
	Pressed,
	Held,
	Released,
};
struct ExecuteCommand
{
	std::shared_ptr<Command> commandPressed ;
	std::shared_ptr<Command> commandHeld;
	std::shared_ptr<Command> commandReleased;
};

class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();
	bool IsPressed(ControllerButton button);
	bool IsHeld(ControllerButton button) ;
	bool IsReleased(ControllerButton button) ;
	void AddCommand(ControllerButton button, ExecuteType type, std::shared_ptr<Command> command);
	void AddCommand(SDL_Scancode button, ExecuteType type, std::shared_ptr<Command> command);

private:
	friend class Singleton<InputManager>;
	XINPUT_STATE m_CurrentState{};
	std::map<ControllerButton, bool>m_IsPresseds;
	//std::map<ControllerButton, std::map<ExecuteType, std::shared_ptr<Command>>> m_CommandsController{};
	std::map<ControllerButton, std::shared_ptr<ExecuteCommand>> m_CommandsController{};
	//std::map<SDL_Scancode, std::map<ExecuteType, std::shared_ptr<Command>>> m_CommandsKeyBoard{};
	std::map<SDL_Scancode, std::shared_ptr<ExecuteCommand>> m_CommandsKeyBoard{};
};


