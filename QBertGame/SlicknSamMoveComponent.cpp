#include "QBertPCH.h"
#include "SlicknSamMoveComponent.h"

#include "BlockManager.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
void SlicknSamMoveComponent::Update(float dt)
{
	if(m_Disabled&&!m_Dead)
	{
		m_RespawnTimer += dt;
		if(m_RespawnDelay<m_RespawnTimer)
		{
			if (m_pGrid.use_count())
			{

				m_RespawnTimer = 0;
				m_Disabled = false;
				m_pGrid.lock()->ResetGridLocation();
				auto pos = m_pGrid.lock()->CalcGridPos();
				m_pTexture.lock()->SetPosition(pos + m_Offset);
			}
		}
		
	}
	else
	{
		Move(dt);
	}
}

void SlicknSamMoveComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}



SlicknSamMoveComponent::SlicknSamMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, 
	const glm::vec3& offset,float respawnDelay, std::weak_ptr<TextureComponent> tex, unsigned short soundId
	, std::weak_ptr<GridComponent> grid, std::shared_ptr<GameObject> QBertPlayer1 , std::shared_ptr<GameObject> QBertPlayer2 )
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_pTexture(tex)
	, m_pGrid(grid)
	, m_MoveTimer(0)
	, m_RespawnTimer(0)
	, m_Dead(false)
	, m_Disabled(false)
	, m_RespawnDelay(respawnDelay)
	, m_SoundId(soundId)
{
	if (QBertPlayer1 != nullptr)
		m_pGridQ1 = QBertPlayer1->GetComponent<GridComponent>();
	if (QBertPlayer2 != nullptr)
		m_pGridQ2 = QBertPlayer2->GetComponent<GridComponent>();
	m_NeedsUpdate = true;
}



void SlicknSamMoveComponent::Move(float dt)
{
	if (m_pGrid.use_count() && m_pTexture.use_count())
	{

		if (m_pGridQ1.use_count())
			if (m_pGrid.lock()->GetGridLocation() == m_pGridQ1.lock()->GetGridLocation())
			{
				m_pGrid.lock()->GridTaken();
				m_pGridQ1.lock()->IncreaseScore(300);
				m_pGrid.lock()->SetGridLocation({ -1,-1 });

				m_Dead = true;
				return;
			}

		if (m_pGridQ2.use_count())
			if (m_pGrid.lock()->GetGridLocation() == m_pGridQ2.lock()->GetGridLocation())
			{
				m_pGrid.lock()->GridTaken();
				m_pGridQ2.lock()->IncreaseScore(300);
				m_pGrid.lock()->SetGridLocation({ -1,-1 });

				m_Dead = true;
				return;
			}
		m_MoveTimer += dt;
		if (m_MoveTimer >= 1.f / m_MoveSpeed)
		{
			glm::ivec2 dir;
			if (rand() % 2 == 0)
				dir = { 0,1 };
			else
				dir = { 1,1 };
			if (m_pGrid.lock()->CheckForDanger(dir))
			{
				m_pTexture.lock()->SetPosition({ -100,-1 ,-1 });
				m_Disabled = true;
			}
			else
			{
				auto pos = m_pGrid.lock()->UpdatePos(dir);
				BlockManager::GetInstance().RevertBlock(m_pGrid.lock()->GetIndex());
				m_pTexture.lock()->SetPosition(pos + m_Offset);
				const auto soundSystem = ServiceLocator::GetSoundSystem();
				if (soundSystem)
				{
					soundSystem->Play(m_SoundId, 15.f);
				}
			}
			m_MoveTimer -= 1.f / m_MoveSpeed;
		}
	}
}
