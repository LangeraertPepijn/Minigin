#pragma once
#include <Minigin.h>
struct QBertMovement;
class GameObject;
class Scene;
class QBertGameApplication :
    public Minigin
{
private:
public:
protected:
	void UserLoadGame() const  override;
	void UserCleanUp() override;
	void UserUpdate(float ) override;
	void CreateBlocks(Scene& scene, const std::string& activeTex, const std::string& inActiveTex, const glm::vec2& blockSize, const glm::vec2& gridSize, const glm::vec2& offset)const;
	std::shared_ptr<GameObject> CreateQBert(Scene& scene, const glm::vec2& gridSize, const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const QBertMovement& movement, const glm::ivec2& gridLoc)const;
};

