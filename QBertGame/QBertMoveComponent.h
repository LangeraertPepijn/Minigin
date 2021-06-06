#pragma once
#include <BaseComponent.h>
class SoundSystem;
class TextureComponent;

class QBertMoveComponent final:public BaseComponent
{
public:
	void Update(float dt)override;
	virtual void SetParent(std::weak_ptr<GameObject> parent);
	bool GetCanMove();
	void Move(const glm::vec3& loc);
	QBertMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,unsigned short soundId);
	virtual ~QBertMoveComponent() = default;
	QBertMoveComponent(const QBertMoveComponent& other) = delete;
	QBertMoveComponent(QBertMoveComponent&& other) = delete;
	QBertMoveComponent& operator=(const QBertMoveComponent& other) = delete;
	QBertMoveComponent& operator=(QBertMoveComponent&& other) = delete;
private:
	float m_MoveTimer;
	float m_MoveSpeed;
	bool m_CanMove;
	std::weak_ptr<TextureComponent> m_pTexComp;
	glm::vec3 m_Offset;
	glm::ivec2 m_MoveDir;
	unsigned short m_MoveSoundId;
};
