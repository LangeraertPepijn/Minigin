#include "QBertPCH.h"
#include "QBertGameApplication.h"
#include "QbertCommands.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "GridComponent.h"
#include "InputManager.h"
#include "BlockManager.h"
#include "HealthComponent.h"
#include "HudManager.h"
#include "HudRenderComponent.h"
#include "QbertMovement.h"
#include "JsonLevelReader.h"
#include "LevelInfo.h"
#include "HudTextComponent.h"
#include "QbertObserver.h"
#include "ResourceManager.h"
#include "SubjectComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
void QBertGameApplication::LoadNextLevel()
{
	m_CurrentLevel++;
	if (m_CurrentLevel >= m_Levels.size())
	{
		Quit();
		return;
	}
	
	BlockManager::GetInstance().Clear();

	auto& scene = SceneManager::GetInstance().CreateScene("QbertScene" + std::to_string(m_Levels[m_CurrentLevel].levelNo));
	
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);

	BlockManager::GetInstance().SetCanRevert(m_Levels[m_CurrentLevel].canRevert);
	BlockManager::GetInstance().SetNeedsDoubleTouch(m_Levels[m_CurrentLevel].needsDoubleTouch);
	BlockManager::GetInstance().SetActiveTex(m_Levels[m_CurrentLevel].activeTex);
	BlockManager::GetInstance().SetInActiveTex(m_Levels[m_CurrentLevel].inActiveTex);
	BlockManager::GetInstance().SetInBetweenTex(m_Levels[m_CurrentLevel].InBetweenTex);
	CreateBlocks(scene, m_Levels[m_CurrentLevel].inActiveTex, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].offset);
	CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, QBertMovement{}, glm::ivec2{ 6,6 });
	QBertMovement movement{ SDL_SCANCODE_X,SDL_SCANCODE_V,SDL_SCANCODE_W,SDL_SCANCODE_R };
	CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, movement, glm::ivec2{ 0,6 });
}

void QBertGameApplication::UserInitialize()
{

}

void QBertGameApplication::UserLoadGame()
{
	JsonLevelReader tet{ "Resources/Level.json" };
	tet.ReadFile(m_Levels);
	BlockManager::GetInstance().LinkLevelDone(m_LevelIsDone);

	auto& scene = SceneManager::GetInstance().CreateScene("QbertScene" + std::to_string(m_Levels[m_CurrentLevel].levelNo));
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);
	BlockManager::GetInstance().SetCanRevert(m_Levels[m_CurrentLevel].canRevert);
	BlockManager::GetInstance().SetNeedsDoubleTouch(m_Levels[m_CurrentLevel].needsDoubleTouch);
	BlockManager::GetInstance().SetActiveTex(m_Levels[m_CurrentLevel].activeTex);
	BlockManager::GetInstance().SetInActiveTex(m_Levels[m_CurrentLevel].inActiveTex);
	BlockManager::GetInstance().SetInBetweenTex(m_Levels[m_CurrentLevel].InBetweenTex);
	CreateBlocks(scene, m_Levels[m_CurrentLevel].inActiveTex, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].offset);
	//CreateQBert(scene, m_Levels[0].gridSize, m_Levels[0].blockSize, m_Levels[0].posFix, m_Levels[0].offset, QBertMovement{}, glm::ivec2{ 6,6 });

	QBertMovement movement{ SDL_SCANCODE_X,SDL_SCANCODE_V,SDL_SCANCODE_W,SDL_SCANCODE_R };
	auto qbert=CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, movement, glm::ivec2{ 0,6 });
	m_SubjectComponent = std::make_shared <SubjectComponent>(qbert);
	m_HealthComponent = std::make_shared <HealthComponent>(qbert, 3);
	m_ScoreComponent = std::make_shared <ScoreComponent>(qbert);

	qbert->AddComponent(m_ScoreComponent);
	qbert->AddComponent(m_SubjectComponent);
	qbert->AddComponent(m_HealthComponent);

	auto hud = HudManager::GetInstance().CreateHud();

	auto go2 = std::make_shared<GameObject>(glm::vec3(100.f, 25.f, 0.f));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto scorep1 = std::make_shared <TextComponent>(go2, " score p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	go2->AddComponent(scorep1);
	auto healthp1 = std::make_shared <TextComponent>(go2, " health p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	go2->AddComponent(healthp1);
	auto observer1 = std::make_shared <ObserverComponent>(go2, std::make_shared<QbertObserver>());
	m_SubjectComponent->AddObserver(observer1);
	go2->AddComponent(observer1);

	hud->AddComponent(std::make_shared<HudRenderComponent>(hud));
	auto scoreHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, " score p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f), "player1 Score:"));
	auto healthHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, " Health p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 5.f, 0.f), "player1 Health:"));

	scorep1->SetHudElement(std::static_pointer_cast<HudTextComponent>(scoreHud1));
	healthp1->SetHudElement(std::static_pointer_cast<HudTextComponent>(healthHud1));
	scene.Add(go2);

}

void QBertGameApplication::UserCleanUp()
{
	 BlockManager::GetInstance().Clear();
}

void QBertGameApplication::UserUpdate(float)
{
	if (m_LevelIsDone)
	{
		LoadNextLevel();
		m_LevelIsDone = false;
	}
}

void QBertGameApplication::CreateBlocks(Scene& scene, const std::string& inActiveTex, const glm::vec2& blockSize, const glm::vec2& gridSize, const glm::vec2& offset)const
{


	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	int locationCounter = 0;


	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i % 2 == 1)
			{

				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(offset.x + (j - i / 2) * blockSize.x - blockSize.x / 2, offset.y + i * blockSize.y, 0);
				auto texComp = std::make_shared <TextureComponent>(go, inActiveTex, pos);
				go->AddComponent(texComp);
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go, gridSize, blockSize,glm::ivec2{j,i},offset));
				BlockManager::GetInstance().AddBlock(int(j* gridSize.x+i),texComp);
				scene.Add(go);
			}
			else
			{
				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(offset.x + (j - i / 2) * blockSize.x , offset.y + i * blockSize.y, 0);
				auto texComp = std::make_shared <TextureComponent>(go, inActiveTex, pos);
				go->AddComponent(texComp);
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go, glm::ivec2{ 7,7 }, blockSize, glm::ivec2{ j,i }, offset));
				BlockManager::GetInstance().AddBlock(int(j* gridSize.x+i),texComp);
				scene.Add(go);
			}
			locationCounter++;
		}
	}
}

std::shared_ptr<GameObject> QBertGameApplication::CreateQBert(Scene& scene,const glm::vec2& gridSize, const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const QBertMovement& movement, const glm::ivec2& gridLoc) const
{
	std::shared_ptr<GameObject> qbert = std::make_shared<GameObject>();
	qbert = std::make_shared<GameObject>();

	auto gridComp = std::make_shared <GridComponent>(qbert, gridSize, blockSize, gridLoc, offset);
	qbert->AddComponent(gridComp);
	auto pos = gridComp->CalcGridPos();
	pos += posFix;
	qbert->AddComponent(std::make_shared <TextureComponent>(qbert, "tempQbert.png", pos));
	qbert->AddComponent(std::make_shared <RenderComponent>(qbert));
	const auto healthComp = std::make_shared<HealthComponent>(qbert, 3);
	qbert->AddComponent(healthComp);
	gridComp->AddHealthComp(healthComp);
	const auto scoreComp = std::make_shared<ScoreComponent>(qbert);
	qbert->AddComponent(scoreComp);
	gridComp->AddScoreComp(scoreComp);
	scene.Add(qbert);


	

	InputManager::GetInstance().AddCommand(movement.LeftDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveLeftDown>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.RightDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveRightDown>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveLeftUp>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.RightUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveRightUp>(qbert, posFix));

	InputManager::GetInstance().AddCommand(movement.RightUpGamepad, ExecuteType::Pressed, std::make_shared<MoveRightUp>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.LeftDownGamepad, ExecuteType::Pressed, std::make_shared<MoveLeftDown>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.RightDownGamepad, ExecuteType::Pressed, std::make_shared<MoveRightDown>(qbert, posFix));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyGamepad, ExecuteType::Pressed, std::make_shared<MoveLeftUp>(qbert, posFix));

	return qbert;
}
