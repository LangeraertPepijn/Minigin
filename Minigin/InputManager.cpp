#include "MiniginPCH.h"
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	auto dwResult =XInputGetState(0, &m_CurrentState);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN)
        {
            for (auto commands : m_CommandsKeyBoard)
            {
                
               for (auto type : commands.second)
                {
                   if (ExecuteType::Pressed == type.first)
                   {

                       if (e.key.keysym.scancode == commands.first)
                       {
                           type.second->Execute();
                       }
                   }
                }
              
            }
		}
        if (e.type == SDL_KEYUP) {
            for (auto commands : m_CommandsKeyBoard)
            {

                for (auto type : commands.second)
                {
                    if (ExecuteType::Released == type.first)
                    {

                        if (e.key.keysym.scancode == commands.first)
                        {
                            type.second->Execute();
                        }
                    }
                }

            }
        }

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}

       
	}
    if (dwResult == ERROR_SUCCESS)
    {
        // Controller is connected
       // std::cout << "ok" << std::endl;
        for (const auto& command : m_CommandsController)
        {
           for (const auto& type : command.second)
            {
                 if (type.first == ExecuteType::Pressed)
                {
                    if (IsPressed(command.first))
                    {
                        type.second->Execute();
                    }

                }
                 else if (type.first == ExecuteType::Held)
                 {

                     if (IsHeld(command.first))
                     {
                         type.second->Execute();
                     }


                 }
                 else if (type.first == ExecuteType::Released)
                 {
                     if (IsReleased(command.first))
                     {
                         type.second->Execute();
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
    auto temp = m_CommandsController[button];
    temp[type]=command;
    m_CommandsController[button]=temp;
    m_IsPresseds[button] = false;
}

void dae::InputManager::AddCommand(SDL_Scancode button, ExecuteType type, std::shared_ptr<Command> command)
{
    auto temp = m_CommandsKeyBoard[button];
    temp[type] = command;
    m_CommandsKeyBoard[button] = temp;
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

