#pragma once
#include <memory>

#include "BaseComponent.h"
class ScoreComponent;
class HealthComponent;


class GridComponent : public BaseComponent
{
public:

	virtual void Update(float)override;



	GridComponent(std::weak_ptr<GameObject> parent, const glm::ivec2& gridCount,const glm::vec2& gridSize, const glm::ivec2& gridLoc,const glm::vec2& offset);

	glm::ivec2 GetGridLocation();
	void AddHealthComp(std::weak_ptr<HealthComponent>health);
	void AddScoreComp(std::weak_ptr<ScoreComponent>score);
	int GetIndex();
	void IncreaseScore();
	glm::vec3 CalcGridPos();
	glm::vec3 UpdatePos(const glm::ivec2& translation);
	virtual ~GridComponent()override = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;
private:
	
	glm::ivec2 m_GridCord;
	glm::ivec2 m_InitialGridCord;
	glm::ivec2 m_GridCount;
	glm::vec2 m_GridSize;
	glm::vec2 m_Offset;
	glm::vec3 m_Pos;
	std::weak_ptr<HealthComponent> m_pHealth;
	std::weak_ptr<ScoreComponent> m_pScore;
};

