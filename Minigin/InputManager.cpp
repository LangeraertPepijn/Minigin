#include "MiniginPCH.h"
#include "InputManager.h"

int PlayerButton::GetCmpValue()const
{
    return ( int(button) + player * 100);
}

bool InputManager::ProcessInput()
{


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN&&e.key.repeat==0)
        {
            for (auto keyCommand : m_CommandsKeyBoard)
            {
                if (e.key.keysym.scancode == keyCommand.first)
                {
                    if (keyCommand.second->commandPressed)
                    {
                        keyCommand.second->commandPressed->Execute();
                    }
                }

            }
		}
        if (e.type == SDL_KEYUP) {
            for (auto keyCommand : m_CommandsKeyBoard)
            {

                if (e.key.keysym.scancode == keyCommand.first)
                {
                    if (keyCommand.second->commandReleased)
                        keyCommand.second->commandReleased->Execute();
                }

            }
        }
        const Uint8* state = SDL_GetKeyboardState(nullptr);
		for (auto keyCommand:m_CommandsKeyBoard)
		{
			if(state[keyCommand.first])
			{
                if (keyCommand.second->commandHeld)
                    keyCommand.second->commandHeld->Execute();
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}

       
	}
    ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    for (DWORD i = 0; i < M_ControllerCount; ++i)
    {
        auto dwResult = XInputGetState(i, &m_CurrentState);

        if (dwResult == ERROR_SUCCESS)
        {
            // Controller is connected

            for (const auto& command : m_CommandsController)
            {
                if (command.first.player == i)
                {

                    if (IsPressed(command.first))
                    {
                        if (command.second->commandPressed)
                            command.second->commandPressed->Execute();
                    }
                    if (IsHeld(command.first))
                    {
                        if (command.second->commandHeld)
                            command.second->commandHeld->Execute();
                    }

                    if (IsReleased(command.first))
                    {
                        if (command.second->commandReleased)
                            command.second->commandReleased->Execute();
                    }
                }
            }

        }
    }
	return true;
}

bool InputManager::IsPressed(const PlayerButton& button)
{

    if (m_CurrentState.Gamepad.wButtons & int(button.button) && !m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = true;
        return true;
    }
    else if (!(m_CurrentState.Gamepad.wButtons & int(button.button)) && m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = false;

    }
    return false;
}

bool InputManager::IsReleased(const PlayerButton& button)
{

    if (m_CurrentState.Gamepad.wButtons & int(button.button) && !m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = true;

    }
    else if (!(m_CurrentState.Gamepad.wButtons & int(button.button)) && m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = false;
        return true;

    }

    return false;
}

void InputManager::AddCommand(ControllerButton button, ExecuteType type, std::shared_ptr<Command> command,DWORD GamepadIndex)
{
    PlayerButton playerButton{ GamepadIndex, button };
    auto temp = m_CommandsController[playerButton];
    if (temp.get() == nullptr)
        temp = std::make_shared<ExecuteCommand>();

	if(type==ExecuteType::Held)
		temp->commandHeld=command;
    else if (type == ExecuteType::Pressed)
        temp->commandPressed = command;
    else if (type == ExecuteType::Released)
        temp->commandReleased = command;
   m_CommandsController[playerButton] = temp;
    m_IsPresseds[playerButton] = false;
}

void InputManager::SetControllerCount(unsigned userCount)
{
    M_ControllerCount = userCount;
}

void InputManager::RefreshControllerCount()
{
    M_ControllerCount = 0;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        const DWORD dwResult = XInputGetState(i, &state);
        if (dwResult == ERROR_SUCCESS)
            ++M_ControllerCount;
    }
}

void InputManager::AddCommand(SDL_Scancode button, ExecuteType type, std::shared_ptr<Command> command)
{
    auto temp = m_CommandsKeyBoard[button];
    if (temp.get() == nullptr)
        temp = std::make_shared<ExecuteCommand>();

    if (type == ExecuteType::Held)
        temp->commandHeld = command;
    else if (type == ExecuteType::Pressed)
        temp->commandPressed = command;
    else if (type == ExecuteType::Released)
        temp->commandReleased = command;
    m_CommandsKeyBoard[button] = temp;
}




bool InputManager::IsHeld(const PlayerButton& button)
{
    if (m_CurrentState.Gamepad.wButtons & int(button.button) && m_IsPresseds.at(button))
    {
        return true;
    }
    if (m_CurrentState.Gamepad.wButtons & int(button.button) && !m_IsPresseds.at(button))
        return true;
    return false;
}

