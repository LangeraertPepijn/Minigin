#pragma once
#include "MiniginPCH.h"
#include "Command.h"

#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"


ScoreCommand::ScoreCommand( std::shared_ptr<ScoreComponent> objectThatScored,int increaseValue)
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

DamageCommand::DamageCommand(std::shared_ptr<GameObject> object, int damage)
	:m_ObjectThatsDamaged(object)
	,m_Damage(damage)
{
}

DamageCommand::~DamageCommand()
{
}

void DamageCommand::Execute()
{
	auto health = m_ObjectThatsDamaged->GetComponent<HealthComponent>();
	health->Damage(m_Damage);
}

PlayCommand::PlayCommand(SoundID id, float volume)
	: m_Id(id)
	, m_Volume(volume)
{
}

PlayCommand::~PlayCommand()
{
}

void PlayCommand::Execute()
{
	const auto soundSystem =ServiceLocator::GetSoundSystem();
	if(soundSystem)
	{
		soundSystem->Play(m_Id, m_Volume);
	}
}
