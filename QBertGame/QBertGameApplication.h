#pragma once
#include <Minigin.h>
#include "LevelInfo.h"
#include "GameMode.h"
class QBertImguiRenderer;
//#include "QBertImguiRenderer.h"
class SubjectComponent;
class ScoreComponent;
class HealthComponent;
class HudTextComponent;
struct CharacterMovement;
class GameObject;
class Scene;


class QBertGameApplication final: public Minigin
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
	QBertImguiRenderer* m_pImguiRenderer;
	bool m_MainMenuIsActive = true;
	void LoadNextLevel();
	void ReloadLevel();
	void ResetLevel();
	void AddCharacterControls(const CharacterMovement& movement,std::shared_ptr<GameObject> object,unsigned long playerId);

public:
protected:
	void UserInitialize() override;
	void UserLoadGame()  override;
	void UserCleanUp() override;
	void UserRender() override;
	void UserUpdate(float ) override;
	void CreateBlocks(Scene& scene)const;
	std::shared_ptr<GameObject> CreateQBert(Scene& scene, const CharacterMovement& movement, const glm::ivec2& gridLoc, unsigned long playerID)const;
	std::shared_ptr<GameObject> CreateCoily(Scene& scene, const glm::ivec2& gridLoc)const;
	std::shared_ptr<GameObject> CreateCoily(Scene& scene, const CharacterMovement& movement, const glm::ivec2& gridLoc,unsigned long controlerID)const;
	std::shared_ptr<GameObject> CreateSlickOrSam(Scene& scene, const glm::ivec2& gridLoc,bool isSlick)const;
	std::shared_ptr<GameObject> CreateUggOrWrongWay(Scene& scene, const glm::ivec2& gridLoc,bool isWrongWay)const;

};

