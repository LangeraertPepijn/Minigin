#include "QBertPCH.h"
#include "SlicknSamMoveComponent.h"

#include "BlockManager.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "TextureComponent.h"
void SlicknSamMoveComponent::Update(float dt)
{
	if(m_Dead)
	{
		m_RespawnTimer += dt;
		if(m_RespawnDelay<m_RespawnTimer)
		{
			m_RespawnTimer = 0;
			m_Dead = false;
			m_pGrid.lock()->ResetGridLocation();
			auto pos = m_pGrid.lock()->CalcGridPos();
			m_pTexture.lock()->SetPosition(pos + m_Offset);
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

void SlicknSamMoveComponent::Reset()
{
}

SlicknSamMoveComponent::SlicknSamMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, 
	const glm::vec3& offset,float respawnDelay, std::weak_ptr<TextureComponent> tex
	, std::weak_ptr<GridComponent> grid, std::shared_ptr<GameObject> QBertPlayer1 , std::shared_ptr<GameObject> QBertPlayer2 )
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_pTexture(tex)
	, m_pGrid(grid)
	, m_MoveTimer(0)
	, m_RespawnTimer(0)
	, m_Dead(false)
	, m_RespawnDelay(respawnDelay)
{
	if (QBertPlayer1 != nullptr)
		m_pGridQ1 = QBertPlayer1->GetComponent<GridComponent>();
	if (QBertPlayer2 != nullptr)
		m_pGridQ2 = QBertPlayer2->GetComponent<GridComponent>();
	m_NeedsUpdate = true;
}



void SlicknSamMoveComponent::Move(float dt)
{
	if(m_pGridQ1.use_count())
	if (m_pGrid.lock()->GetGridLocation() == m_pGridQ1.lock()->GetGridLocation())
		{
			m_pGrid.lock()->GridTaken();
			m_pGridQ1.lock()->IncreaseScore(300);
			m_pGrid.lock()->SetGridLocation({ -1,-1 });


			return;
		}

	if(m_pGridQ2.use_count())
		if (m_pGrid.lock()->GetGridLocation() == m_pGridQ2.lock()->GetGridLocation())
		{
			m_pGrid.lock()->GridTaken();
			m_pGridQ2.lock()->IncreaseScore(300);
			m_pGrid.lock()->SetGridLocation({ -1,-1 });

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
			m_Dead = true;
		}
		else
		{
			auto pos = m_pGrid.lock()->UpdatePos(dir);
			BlockManager::GetInstance().RevertBlock(m_pGrid.lock()->GetIndex());
			m_pTexture.lock()->SetPosition(pos + m_Offset);
		}
		m_MoveTimer -= 1.f / m_MoveSpeed;
	}
}
