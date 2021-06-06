#pragma once
#include <BaseComponent.h>
class GridComponent;
class TextureComponent;

class UggnWrongWayMoveComponent final :
    public BaseComponent
{
public:

	void Update(float dt)override;
	virtual void SetParent(std::weak_ptr<GameObject> parent);
	void Reset();
	UggnWrongWayMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed,
		const glm::vec3& offset, float respawnDelay, const glm::vec3& qbertOffset, unsigned short soundId,
		std::shared_ptr<GameObject> QBertPlayer1 = nullptr, std::shared_ptr<GameObject> QBertPlayer2 = nullptr,
		bool movesRight=true);
	virtual ~UggnWrongWayMoveComponent() = default;
	UggnWrongWayMoveComponent(const UggnWrongWayMoveComponent& other) = delete;
	UggnWrongWayMoveComponent(UggnWrongWayMoveComponent&& other) = delete;
	UggnWrongWayMoveComponent& operator=(const UggnWrongWayMoveComponent& other) = delete;
	UggnWrongWayMoveComponent& operator=(UggnWrongWayMoveComponent&& other) = delete;
private:
	void Move(float dt);
	float m_MoveTimer;
	float m_RespawnTimer;
	float m_MoveSpeed;
	float m_RespawnDelay;
	bool m_Dead;
	std::vector<glm::ivec2> m_Dirs;
	glm::vec3 m_Offset;
	glm::vec3 m_QBertOffset;
	std::shared_ptr<TextureComponent> m_pTexture;
	std::shared_ptr<GridComponent> m_pGrid;
	std::shared_ptr<GridComponent> m_pGridQ1;
	std::shared_ptr<TextureComponent> m_pTexQ1;
	std::shared_ptr<GridComponent> m_pGridQ2;
	std::shared_ptr<TextureComponent> m_pTexQ2;
	unsigned short m_SoundId;

};

