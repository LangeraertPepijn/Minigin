#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include "Command.h"
namespace dae
{
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

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button);
		bool IsHeld(ControllerButton button) ;
		bool IsReleased(ControllerButton button) ;
		void AddCommand(ControllerButton button, ExecuteType type, std::shared_ptr<Command> command);
	private:
		friend class Singleton<InputManager>;
		XINPUT_STATE m_CurrentState{};
		std::map<ControllerButton, bool>m_IsPresseds;
		std::map<ExecuteType, std::map<ControllerButton, std::shared_ptr<Command>>> m_Comands{};
	};

}
