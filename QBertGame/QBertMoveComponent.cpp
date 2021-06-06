#include "QBertPCH.h"
#include "QBertMoveComponent.h"
#include "iostream"
#include "GameObject.h"
#include "SDLMixerSoundSystem.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"

void QBertMoveComponent::Update(float dt)
{
	if (!m_CanMove)
	{
		m_MoveTimer += dt;
		if (m_MoveTimer >= 1.f / m_MoveSpeed)
		{
			m_CanMove = true;
			m_MoveTimer = 0;
		}
	
	}
}

void QBertMoveComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
	m_pTexComp = parent.lock()->GetComponent<TextureComponent>();
}

bool QBertMoveComponent::GetCanMove()
{
	return m_CanMove;
}

QBertMoveComponent::QBertMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,unsigned short moveSoundID)
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_MoveTimer(0)
	, m_CanMove(true)
	, m_MoveDir()
	, m_MoveSoundId(moveSoundID)
	 
{
	m_NeedsUpdate = true;
	m_pTexComp=parent.lock()->GetComponent<TextureComponent>();
	
}

void QBertMoveComponent::Move( const glm::vec3& loc)
{


	
	const auto soundSystem = ServiceLocator::GetSoundSystem();
	if (soundSystem)
	{
		soundSystem->Play(m_MoveSoundId, 15.f);
	}
	if(m_pTexComp.use_count())
		m_pTexComp.lock()->SetPosition(loc +  m_Offset);
	m_CanMove = false;
}
