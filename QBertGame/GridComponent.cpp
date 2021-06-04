#include "QBertPCH.h"
#include "GridComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

void GridComponent::Update(float)
{
}


GridComponent::GridComponent(std::weak_ptr<GameObject> parent, const glm::ivec2& gridCount, const glm::vec2& gridSize, const glm::ivec2& gridLoc,
	const glm::vec2& offset)
	: BaseComponent(parent)
	, m_GridSize(gridSize)
	, m_GridCount(gridCount)
	, m_Offset(offset)
	, m_GridCord(gridLoc)
	, m_InitialGridCord(gridLoc)
{
}

glm::ivec2 GridComponent::GetGridLocation()
{
	return m_GridCord;
}

void GridComponent::AddHealthComp(std::weak_ptr<HealthComponent> health)
{
	m_pHealth = health;
}

void GridComponent::AddScoreComp(std::weak_ptr<ScoreComponent> score)
{
	m_pScore = score;
}


glm::vec3 GridComponent::UpdatePos(const glm::ivec2& translation)
{
	if (!m_pHealth.expired())
		if (m_pHealth.lock()->GetHealth() <= 0)
			return {20,10,-1};
	
	m_GridCord += translation;
	//cap to play field
	if (m_GridCord.x > m_GridCord.y||m_GridCord.x<0||m_GridCord.y<0|| m_GridCord.x>m_GridCount.x || m_GridCord.y>m_GridCount.y)
	{
		m_GridCord = m_InitialGridCord;
		auto pos = CalcGridPos();
		pos.z = -1;
		if(!m_pHealth.expired())
		{
			m_pHealth.lock()->Damage(1);
			if (m_pHealth.lock()->GetHealth() <= 1)
				return pos;
		}
		
		return pos;
	}
	return CalcGridPos();
}

int GridComponent::GetIndex()
{

	return int(m_GridCord.x * m_GridCount.x + m_GridCord.y);
}

void GridComponent::IncreaseScore()
{
	if (!m_pScore.expired())
		m_pScore.lock()->IncreaseScore(25);
		
}

glm::vec3 GridComponent::CalcGridPos()
{

	if(m_GridCord.y%2==1)
		return  glm::vec3(m_Offset.x + (m_GridCord.x - m_GridCord.y / 2) * m_GridSize.x - m_GridSize.x / 2, m_Offset.y + m_GridCord.y * m_GridSize.y, 0);
	else 
			
		return   glm::vec3(m_Offset.x + (m_GridCord.x - m_GridCord.y / 2) * m_GridSize.x, m_Offset.y + m_GridCord.y * m_GridSize.y, 0);


}
