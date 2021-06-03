#include "MiniginPCH.h"
#include "InputManager.h"

bool InputManager::ProcessInput()
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
            for (auto keyCommand : m_CommandsKeyBoard)
            {
                if (e.key.keysym.scancode == keyCommand.first)
                {
                    if (keyCommand.second->commandPressed)
                        keyCommand.second->commandPressed->Execute();
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
    if (dwResult == ERROR_SUCCESS)
    {
        // Controller is connected

        for (const auto& command : m_CommandsController)
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

	return true;
}

bool InputManager::IsPressed(ControllerButton button)
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

bool InputManager::IsReleased(ControllerButton button)
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

void InputManager::AddCommand(ControllerButton button, ExecuteType type, std::shared_ptr<Command> command)
{
    auto temp = m_CommandsController[button];
    if (temp.get() == nullptr)
        temp = std::make_shared<ExecuteCommand>();

	if(type==ExecuteType::Held)
		temp->commandHeld=command;
    else if (type == ExecuteType::Pressed)
        temp->commandPressed = command;
    else if (type == ExecuteType::Released)
        temp->commandReleased = command;
    m_IsPresseds[button] = false;
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


bool InputManager::IsHeld(ControllerButton button)
{
    if (m_CurrentState.Gamepad.wButtons & int(button) && m_IsPresseds.at(button))
    {
        return true;
    }
    if (m_CurrentState.Gamepad.wButtons & int(button) && !m_IsPresseds.at(button))
        return true;
    return false;
}

