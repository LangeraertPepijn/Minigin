#pragma once
#include "MiniginPCH.h"
#include "Command.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"


ScoreCommand::ScoreCommand( std::shared_ptr<dae::ScoreComponent> objectThatScored,int increaseValue)
	:m_ScoreComponent(objectThatScored)
	,m_IncreaseValue(increaseValue)
{
}

ScoreCommand::~ScoreCommand()
{
}

void ScoreCommand::Execute()
{
	
	m_ScoreComponent->IncreaseScore(m_IncreaseValue);
}

QuitCommand::QuitCommand(bool* quit)
	:m_Quit{quit}
{

}

QuitCommand::~QuitCommand()
{
}

DamageCommand::DamageCommand(std::shared_ptr<dae::GameObject> object, int damage)
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
