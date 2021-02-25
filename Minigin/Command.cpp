#pragma once
#include "MiniginPCH.h"
#include "Command.h"

JumpCommand::JumpCommand()
{
}

JumpCommand::~JumpCommand()
{
}

DuckCommand::DuckCommand()
{
}

DuckCommand::~DuckCommand()
{
}

FartCommand::FartCommand()
{
}

FartCommand::~FartCommand()
{
}

FireCommand::FireCommand()
{
}

FireCommand::~FireCommand()
{
}



QuitCommand::QuitCommand(bool* quit)
	:m_Quit{quit}
{

}

QuitCommand::~QuitCommand()
{
}
