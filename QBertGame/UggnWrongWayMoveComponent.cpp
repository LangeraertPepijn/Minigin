#include "QBertPCH.h"
#include "UggnWrongWayMoveComponent.h"
#include "BlockManager.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "TextureComponent.h"
void UggnWrongWayMoveComponent::Update(float dt)
{
	if (m_Dead)
	{
		m_RespawnTimer += dt;
		if (m_RespawnDelay < m_RespawnTimer)
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

void UggnWrongWayMoveComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}

void UggnWrongWayMoveComponent::Reset()
{
}

UggnWrongWayMoveComponent::UggnWrongWayMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,
	float respawnDelay, const glm::vec3& qbertOffset,std::shared_ptr<GameObject> QBertPlayer1,
	std::shared_ptr<GameObject> QBertPlayer2, bool isMovingLeft)
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_QBertOffset(qbertOffset)
	, m_MoveTimer(0)
	, m_RespawnTimer(0)
	, m_Dead(false)
	, m_RespawnDelay(respawnDelay)
{
	m_pTexture=m_pParent.lock()->GetComponent<TextureComponent>();
	m_pGrid=m_pParent.lock()->GetComponent<GridComponent>();
	if(isMovingLeft)
	{
		
		m_Dirs.push_back({ 0,-1 });
		m_Dirs.push_back({ 1,0 });
	}
	else
	{
		m_Dirs.push_back({ -1,0 });
		m_Dirs.push_back({ -1,-1 });
	}
	if (QBertPlayer1 != nullptr)
	{
		m_pGridQ1 = QBertPlayer1->GetComponent<GridComponent>();
		m_pTexQ1 = QBertPlayer1->GetComponent<TextureComponent>();
		
	}
	if (QBertPlayer2 != nullptr)
	{
		
		m_pTexQ2 = QBertPlayer2->GetComponent<TextureComponent>();
		m_pGridQ2 = QBertPlayer2->GetComponent<GridComponent>();
	}
	m_NeedsUpdate = true;
	m_Dead = true;
	m_pTexture.lock()->SetPosition({ -100,-1 ,-1 });
}

void UggnWrongWayMoveComponent::Move(float dt)
{
	if (m_pGridQ1.use_count())
		if (m_pGrid.lock()->GetGridLocation() == m_pGridQ1.lock()->GetGridLocation())
		{
			auto pos =m_pGridQ1.lock()->GridTaken();
			m_pTexQ1.lock()->SetPosition(pos + m_QBertOffset);
			return;
		}

	if (m_pGridQ2.use_count())
		if (m_pGrid.lock()->GetGridLocation() == m_pGridQ2.lock()->GetGridLocation())
		{
			auto pos = m_pGridQ2.lock()->GridTaken();
			m_pTexQ1.lock()->SetPosition(pos + m_QBertOffset);
			return;
		}

	m_MoveTimer += dt;
	if (m_MoveTimer >= 1.f / m_MoveSpeed)
	{
		auto idx = rand() % m_Dirs.size();
		
		glm::ivec2 dir = m_Dirs[idx];
		auto checkDir = dir*2;
		if (m_pGrid.lock()->CheckForDanger(checkDir))
		{
			m_pTexture.lock()->SetPosition({ -100,-1 ,-1 });
			m_Dead = true;
		}
		else
		{
			auto pos = m_pGrid.lock()->UpdatePos(dir);
			m_pTexture.lock()->SetPosition(pos + m_Offset);
		}
		m_MoveTimer -= 1.f / m_MoveSpeed;
	}
}
