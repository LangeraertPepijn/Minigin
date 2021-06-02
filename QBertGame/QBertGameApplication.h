#pragma once
#include <Minigin.h>
class GameObject;
class Scene;

class QBertGameApplication :
    public Minigin
{
private:
	glm::vec2 m_Offset = { 288,40 };
	glm::vec2 m_BlockSize = { 64,45 };
	glm::vec3 m_PosFix{ 20, -10,0 };
public:
protected:
	void UserLoadGame() const  override;
	void UserCleanUp() override;
	void CreateBlocks(Scene& scene)const;
	std::shared_ptr<GameObject> CreateQBert(Scene& scene)const;
};

