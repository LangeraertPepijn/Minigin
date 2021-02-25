#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	auto dwResult =XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
    if (dwResult == ERROR_SUCCESS)
    {
        // Controller is connected
       // std::cout << "ok" << std::endl;
        for (const auto& command : m_Comands)
        {
            if (command.first == ExecuteType::Pressed)
            {
                for (const auto& temp : command.second)
                {
                    if (IsPressed(temp.first))
                    {
                        temp.second->Execute();
                    }

                }
            }
            else if (command.first == ExecuteType::Held)
            {
                for (const auto& temp : command.second)
                {
                    if (IsHeld(temp.first))
                    {
                        temp.second->Execute();
                    }

                }
            }
            else if (command.first == ExecuteType::Released)
            {
                for (const auto& temp : command.second)
                {

                    if (IsReleased(temp.first))
                    {
                        temp.second->Execute();
                    }

                }
            }

        }


    }

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button)
{

    if (m_CurrentState.Gamepad.wButtons & int(button) && !m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = true;
        return true;
    }
    else if (!(m_CurrentState.Gamepad.wButtons & int(button)) && m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = false;

    }
    return false;
}

bool dae::InputManager::IsReleased(ControllerButton button)
{

    if (m_CurrentState.Gamepad.wButtons & int(button) && !m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = true;

    }
    else if (!(m_CurrentState.Gamepad.wButtons & int(button)) && m_IsPresseds.at(button))
    {
        m_IsPresseds[button] = false;
        return true;

    }

    return false;
}

void dae::InputManager::AddCommand(ControllerButton button, ExecuteType type, std::shared_ptr<Command> command)
{
        auto temp = m_Comands[type];
    temp[button]=command;
    m_Comands[type]=temp;
    m_IsPresseds[button] = false;
}

bool dae::InputManager::IsHeld(ControllerButton button)
{
    if (m_CurrentState.Gamepad.wButtons & int(button) && m_IsPresseds.at(button))
    {
        return true;
    }
    if (m_CurrentState.Gamepad.wButtons & int(button) && !m_IsPresseds.at(button))
        return true;
    return false;
}

