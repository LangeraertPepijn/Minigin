#pragma once
#include <BaseComponent.h>
class GridComponent;
class TextureComponent;

class UggMoveComponent :
    public BaseComponent
{
public:

	void Update(float dt)override;
	virtual void SetParent(std::weak_ptr<GameObject> parent);
	void Reset();
	UggMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset, float respawnDelay, std::weak_ptr<TextureComponent> tex, std::weak_ptr<GridComponent> grid, std::shared_ptr<GameObject> QBertPlayer1 = nullptr, std::shared_ptr<GameObject> QBertPlayer2 = nullptr);
	virtual ~UggMoveComponent() = default;
	UggMoveComponent(const UggMoveComponent& other) = delete;
	UggMoveComponent(UggMoveComponent&& other) = delete;
	UggMoveComponent& operator=(const UggMoveComponent& other) = delete;
	UggMoveComponent& operator=(UggMoveComponent&& other) = delete;
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

