#pragma once
#include "MiniginPCH.h"
#include "Command.h"
#include "TextComponent.h"
#include "HealthComponent.h"
JumpCommand::JumpCommand()
{
}

JumpCommand::~JumpCommand()
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

DieCommand::DieCommand(std::shared_ptr<dae::GameObject> object)
	:m_ObjectThatDies(object)
{
}

DieCommand::~DieCommand()
{
}

void DieCommand::Execute()
{
	
		auto temp = m_ObjectThatDies->GetComponent<dae::TextComponent>();
	if(temp)
		temp->SetText("Rip you");
	
}


QuitCommand::QuitCommand(bool* quit)
	:m_Quit{quit}
{

}

QuitCommand::~QuitCommand()
{
}

DamageCommand::DamageCommand(std::shared_ptr<dae::GameObject> object, float damage)
	:m_ObjectThatsDamaged(object)
	,m_Damage(damage)
{
}

DamageCommand::~DamageCommand()
{
}

void DamageCommand::Execute()
{
	auto health = m_ObjectThatsDamaged->GetComponent<dae::HealthComponent>();
	health->Damage(m_Damage);
}
