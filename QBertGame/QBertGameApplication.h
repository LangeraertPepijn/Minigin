#pragma once
#include <Minigin.h>
#include "LevelInfo.h"
class SubjectComponent;
class ScoreComponent;
class HealthComponent;
class HudTextComponent;
struct CharacterMovement;
class GameObject;
class Scene;
enum class GameMode: int
{
	SinglePlayer,
	MultiPlayerCoop,
	MultiPlayerVS
	
};
class QBertGameApplication : public Minigin
{
private:
	std::vector<LevelInfo> m_Levels;
	int m_CurrentLevelIdx=0;
	bool m_LevelIsDone=false;
	GameMode m_GameMode = GameMode::SinglePlayer;
	
	std::shared_ptr<GameObject> m_pQBert1=nullptr;
	std::shared_ptr<GameObject> m_pQBert2=nullptr;
	std::shared_ptr<GameObject> m_pHudObj=nullptr;
	std::shared_ptr<HudTextComponent> m_pHudScore=nullptr;
	std::shared_ptr<HudTextComponent> m_pHudHealth=nullptr;

	
	void LoadNextLevel();
	void ReloadLevel();

public:
protected:
	void UserInitialize() override;
	void UserLoadGame()  override;
	void UserCleanUp() override;
	void UserUpdate(float ) override;
	void CreateBlocks(Scene& scene)const;
	std::shared_ptr<GameObject> CreateQBert(Scene& scene, const CharacterMovement& movement, const glm::ivec2& gridLoc, int playerID)const;
	std::shared_ptr<GameObject> CreateCoily(Scene& scene, const glm::ivec2& gridLoc)const;
	std::shared_ptr<GameObject> CreateCoily(Scene& scene, const CharacterMovement& movement, const glm::ivec2& gridLoc)const;
	std::shared_ptr<GameObject> CreateSlickOrSam(Scene& scene, const glm::ivec2& gridLoc,bool isSlick)const;
	std::shared_ptr<GameObject> CreateUggOrWrongWay(Scene& scene, const glm::ivec2& gridLoc,bool isWrongWay)const;

};

