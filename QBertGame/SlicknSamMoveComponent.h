#pragma once
#include <BaseComponent.h>
class GridComponent;
class TextureComponent;

class SlicknSamMoveComponent :
    public BaseComponent
{
public:

	void Update(float dt)override;
	virtual void SetParent(std::weak_ptr<GameObject> parent);
	void Reset();
	SlicknSamMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,float respawnDelay, std::weak_ptr<TextureComponent> tex, std::weak_ptr<GridComponent> grid, std::shared_ptr<GameObject> QBertPlayer1=nullptr, std::shared_ptr<GameObject> QBertPlayer2=nullptr);
	virtual ~SlicknSamMoveComponent() = default;
	SlicknSamMoveComponent(const SlicknSamMoveComponent& other) = delete;
	SlicknSamMoveComponent(SlicknSamMoveComponent&& other) = delete;
	SlicknSamMoveComponent& operator=(const SlicknSamMoveComponent& other) = delete;
	SlicknSamMoveComponent& operator=(SlicknSamMoveComponent&& other) = delete;
private:
	void Move(float dt);
	float m_MoveTimer;
	float m_RespawnTimer;
	float m_MoveSpeed;
	float m_RespawnDelay;
	bool m_Dead;
	glm::vec3 m_Offset;
	std::weak_ptr<TextureComponent> m_pTexture;
	std::weak_ptr<GridComponent> m_pGrid;
	std::weak_ptr<GridComponent> m_pGridQ1;
	std::weak_ptr<GridComponent> m_pGridQ2;


};

