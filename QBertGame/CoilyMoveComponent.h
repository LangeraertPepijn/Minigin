#pragma once
#include <BaseComponent.h>
class GridComponent;
class TextureComponent;

class CoilyMoveComponent :
    public BaseComponent
{

public:

	void Update(float dt)override;
	virtual void SetParent(std::weak_ptr<GameObject> parent);
	bool* GetCanMove();
	void SetMoved(bool moved);
	void Reset();
	CoilyMoveComponent(std::weak_ptr<GameObject> parent,float moveSpeed,const glm::vec3& offset,
		const glm::vec3& activeOffset ,std::weak_ptr<GameObject> qbert1, std::weak_ptr<GameObject> qbert2 , const std::string& inActiveTex,const std::string& activeTex,bool isControlled);
	virtual ~CoilyMoveComponent() = default;
	CoilyMoveComponent(const CoilyMoveComponent& other) = delete;
	CoilyMoveComponent(CoilyMoveComponent&& other) = delete;
	CoilyMoveComponent& operator=(const CoilyMoveComponent& other) = delete;
	CoilyMoveComponent& operator=(CoilyMoveComponent&& other) = delete;
private:
	void Move(float dt);
	float m_MoveTimer;
	float m_MoveSpeed;
	bool m_LockUpDir;
	bool m_IsControlled;
	bool m_Moved;
	std::vector<glm::ivec2> m_Dirs;
	glm::vec3 m_Offset;
	glm::vec3 m_OffsetActive;
	std::string m_ActiveTex;
	std::string m_InActiveTex;
	std::weak_ptr<TextureComponent> m_pTexture;
	std::weak_ptr<TextureComponent> m_pTextureTargetQ1;
	std::weak_ptr<TextureComponent> m_pTextureTargetQ2;
	std::weak_ptr<GridComponent> m_pGrid;
	std::weak_ptr<GridComponent> m_pTargetQ1;
	std::weak_ptr<GridComponent> m_pTargetQ2;
};

