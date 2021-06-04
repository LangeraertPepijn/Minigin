#pragma once
#include <Minigin.h>
#include "LevelInfo.h"
class SubjectComponent;
class ScoreComponent;
class HealthComponent;
struct QBertMovement;
class GameObject;
class Scene;
class QBertGameApplication : public Minigin
{
private:
	std::vector<LevelInfo> m_Levels;
	int m_CurrentLevel=0;
	bool m_LevelIsDone=false;;
	std::shared_ptr<GameObject> m_QBert1;
	void LoadNextLevel();
public:
protected:
	void UserInitialize() override;
	void UserLoadGame()  override;
	void UserCleanUp() override;
	void UserUpdate(float ) override;
	void CreateBlocks(Scene& scene, const std::string& inActiveTex, const glm::vec2& blockSize, const glm::vec2& gridSize, const glm::vec2& offset)const;
	std::shared_ptr<GameObject> CreateQBert(Scene& scene, const glm::vec2& gridSize, const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const QBertMovement& movement, const glm::ivec2& gridLoc)const;
	std::shared_ptr<GameObject> CreateCoily(Scene& scene, const glm::vec2& gridSize, const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const glm::ivec2& gridLoc)const;
};

