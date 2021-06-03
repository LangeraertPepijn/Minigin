#include "QBertPCH.h"
#include "GridComponent.h"

void GridComponent::Update(float)
{
}


GridComponent::GridComponent(std::weak_ptr<GameObject> parent, const glm::ivec2& gridCount, const glm::vec2& gridSize, const glm::ivec2& gridLoc,
	const glm::vec2& offset)
	: BaseComponent(parent)
	, m_GridSize(gridSize)
	, m_GridCount(gridCount)
	, m_Offset(offset)
	,m_GridCord(gridLoc)
{
}

glm::ivec2 GridComponent::GetGridLocation()
{
	return m_GridCord;
}


glm::vec3 GridComponent::UpdatePos(const glm::ivec2& translation)
{
	m_GridCord += translation;
	//cap to play field
	if (m_GridCord.x > m_GridCord.y||m_GridCord.x<0||m_GridCord.y<0|| m_GridCord.x>m_GridCount.x || m_GridCord.y>m_GridCount.y)
		m_GridCord = { 0,0 };
	return CalcGridPos();
}

int GridComponent::GetIndex()
{

	return int(m_GridCord.x * m_GridCount.x + m_GridCord.y);
}

glm::vec3 GridComponent::CalcGridPos()
{

	if(m_GridCord.y%2==1)
		return  glm::vec3(m_Offset.x + (m_GridCord.x - m_GridCord.y / 2) * m_GridSize.x - m_GridSize.x / 2, m_Offset.y + m_GridCord.y * m_GridSize.y, 0);
	else 
			
		return   glm::vec3(m_Offset.x + (m_GridCord.x - m_GridCord.y / 2) * m_GridSize.x, m_Offset.y + m_GridCord.y * m_GridSize.y, 0);


}
