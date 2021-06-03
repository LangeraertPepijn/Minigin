#pragma once
#include <memory>

#include "BaseComponent.h"


class GridComponent : public BaseComponent
{
public:

	virtual void Update(float)override;



	GridComponent(std::weak_ptr<GameObject> parent, const glm::ivec2& gridCount,const glm::vec2& gridSize, const glm::ivec2& gridLoc,const glm::vec2& offset);

	glm::ivec2 GetGridLocation();
	void CalcGridLocation();
	int GetIndex();
	glm::vec3 CalcGridPos();
	glm::vec3 UpdatePos(const glm::ivec2& translation);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;
private:
	
	glm::ivec2 m_GridCord;
	glm::ivec2 m_GridCount;
	glm::vec2 m_GridSize;
	glm::vec2 m_Offset;
	glm::vec3 m_Pos;
};

