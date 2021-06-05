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
#include "CharacterMovement.h"
#include "JsonLevelReader.h"
#include "LevelInfo.h"
#include "HudTextComponent.h"
#include "CoilyMoveComponent.h"
#include "QbertHealthObserver.h"
#include "QbertObserver.h"
#include "ResourceManager.h"
#include "SubjectComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
void QBertGameApplication::LoadNextLevel()
{

	m_CurrentLevel++;
	if (size_t(m_CurrentLevel) >= m_Levels.size())
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

	auto gridComp = m_pQBert1->GetComponent<GridComponent>();
	gridComp->ResetGridLocation();
	auto pos = gridComp->CalcGridPos();
	m_pQBert1->GetComponent<TextureComponent>()->SetPosition(pos + m_Levels[m_CurrentLevel].posFix);
	scene.Add(m_pQBert1);

	switch (m_GameMode)
	{
	case GameMode::SinglePlayer:
	{

		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
		break;
	}
	case GameMode::MultiPlayerCoop:
	{
		auto gridComp2 = m_pQBert2->GetComponent<GridComponent>();
		gridComp2->ResetGridLocation();
		auto pos2 = gridComp2->CalcGridPos();
		m_pQBert2->GetComponent<TextureComponent>()->SetPosition(pos2 + m_Levels[m_CurrentLevel].posFix);
		scene.Add(m_pQBert2);
		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
		break;
	}
	case GameMode::MultiPlayerVS:
	{
		const CharacterMovement movement{ SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A,SDL_SCANCODE_W };
		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, movement, glm::ivec2{ rand() % 2,1 });
		break;
	}
	}


	

}

void QBertGameApplication::ReloadLevel()
{
	BlockManager::GetInstance().Clear();

	m_pQBert1->GetComponent<HealthComponent>()->Heal(3);
	m_pQBert1->GetComponent<ScoreComponent>()->SetScore(0);
	
	auto& scene = SceneManager::GetInstance().CreateScene("QbertScene" + std::to_string(m_Levels[m_CurrentLevel].levelNo));

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);

	auto gridComp = m_pQBert1->GetComponent<GridComponent>();
	gridComp->ResetGridLocation();
	auto pos = gridComp->CalcGridPos();
	m_pQBert1->GetComponent<TextureComponent>()->SetPosition(pos + m_Levels[m_CurrentLevel].posFix);
	scene.Add(m_pQBert1);
	
	BlockManager::GetInstance().SetCanRevert(m_Levels[m_CurrentLevel].canRevert);
	BlockManager::GetInstance().SetNeedsDoubleTouch(m_Levels[m_CurrentLevel].needsDoubleTouch);
	BlockManager::GetInstance().SetActiveTex(m_Levels[m_CurrentLevel].activeTex);
	BlockManager::GetInstance().SetInActiveTex(m_Levels[m_CurrentLevel].inActiveTex);
	BlockManager::GetInstance().SetInBetweenTex(m_Levels[m_CurrentLevel].InBetweenTex);
	CreateBlocks(scene, m_Levels[m_CurrentLevel].inActiveTex, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].offset);
	switch (m_GameMode)
	{
	case GameMode::SinglePlayer:
	{

		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
		break;
	}
	case GameMode::MultiPlayerCoop:
	{
		auto gridComp2 = m_pQBert2->GetComponent<GridComponent>();
		gridComp2->ResetGridLocation();
		auto pos2 = gridComp2->CalcGridPos();
		m_pQBert2->GetComponent<TextureComponent>()->SetPosition(pos2 + m_Levels[m_CurrentLevel].posFix);
		scene.Add(m_pQBert2);
		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
		break;
	}
	case GameMode::MultiPlayerVS:
	{
		const CharacterMovement movement{ SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A,SDL_SCANCODE_W };
		CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, movement, glm::ivec2{ rand() % 2,1 });
		break;
	}
	}
	
}

void QBertGameApplication::UserInitialize()
{
	std::srand(unsigned int(time(NULL)));
}

void QBertGameApplication::UserLoadGame()
{
	m_GameMode = GameMode::MultiPlayerVS;
	JsonLevelReader jsonReader{ "Resources/Level.json" };
	jsonReader.ReadFile(m_Levels);
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
	std::shared_ptr<GameObject> coily = nullptr;
	switch (m_GameMode)
	{
		case GameMode::SinglePlayer:
		{

			m_pQBert1 = CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, CharacterMovement{}, glm::ivec2{ 0,0 },0);
			coily=CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
			break;
		}
		case GameMode::MultiPlayerCoop:
		{

			m_pQBert1 = CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, CharacterMovement{}, glm::ivec2{ 6,6 },0);
			const CharacterMovement movement{ SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A,SDL_SCANCODE_W };
			m_pQBert2 = CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, movement, glm::ivec2{ 0,6 },1);

			coily = CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, glm::ivec2{ rand() % 2,1 });
			break;
		}
		case GameMode::MultiPlayerVS:
		{

			m_pQBert1 = CreateQBert(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset, CharacterMovement{}, glm::ivec2{ 0,0 },0);
			const CharacterMovement movement{ SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A,SDL_SCANCODE_W };
			coily = CreateCoily(scene, m_Levels[m_CurrentLevel].gridSize, m_Levels[m_CurrentLevel].blockSize, m_Levels[m_CurrentLevel].posFix, m_Levels[m_CurrentLevel].offset,movement, glm::ivec2{ rand() % 2,1 });
			break;
		}
	}


	

	

	auto subjComp = std::make_shared <SubjectComponent>(m_pQBert1);
	std::shared_ptr<SubjectComponent> subjComp2 = nullptr;
	m_pQBert1->AddComponent(subjComp);
	if (m_GameMode == GameMode::MultiPlayerCoop)
	{
		subjComp2 = std::make_shared <SubjectComponent>(m_pQBert2);
		auto healthComp = m_pQBert1->GetComponent<HealthComponent>();
		auto scoreComp = m_pQBert1->GetComponent<ScoreComponent>();
		auto gridComp = m_pQBert2->GetComponent<GridComponent>();
		gridComp->AddHealthComp(healthComp);
		gridComp->AddScoreComp(scoreComp);
		m_pQBert2->AddComponent(healthComp);
		m_pQBert2->AddComponent(scoreComp);
		m_pQBert2->AddComponent(subjComp2);
	}

	auto hud = HudManager::GetInstance().CreateHud();

	auto go2 = std::make_shared<GameObject>(glm::vec3(100.f, 25.f, 0.f));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto scorep1 = std::make_shared <TextComponent>(go2, " score p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	go2->AddComponent(scorep1);
	auto healthp1 = std::make_shared <TextComponent>(go2, " health p1", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(100.f, 25.f, 0.f));
	go2->AddComponent(healthp1);
	auto observer1 = std::make_shared <ObserverComponent>(go2, std::make_shared<QbertObserver>());
	subjComp->AddObserver(observer1);
	
	subjComp->AddObserver(coily->GetComponent<ObserverComponent>());
	if(subjComp2!=nullptr)
		subjComp2->AddObserver(observer1);
	go2->AddComponent(observer1);

	hud->AddComponent(std::make_shared<HudRenderComponent>(hud));
	auto scoreHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, "QBertScore: 0", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(400.f, 25.f, 0.f), "QBertScore: "));
	auto healthHud1 = hud->AddComponent(std::make_shared<HudTextComponent>(hud, "Health: 3", font, glm::tvec3<uint8_t> { 255, 255, 0 }, glm::vec3(400.f, 5.f, 0.f), "Health: "));

	
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
	//if (m_pQBert1->GetComponent<HealthComponent>()->GetHealth()==0)
	//{
	//	ReloadLevel();
	//}
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
				go->SetTag("Block");
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
/// <summary>
/// creates coily but needs to have a qbert to do so
/// </summary>
/// <param name="scene"></param>
/// <param name="gridSize"></param>
/// <param name="blockSize"></param>
/// <param name="posFix"></param>
/// <param name="offset"></param>
/// <param name="movement"></param>
/// <param name="gridLoc"></param>
/// <returns></returns>
std::shared_ptr<GameObject> QBertGameApplication::CreateQBert(Scene& scene,const glm::vec2& gridSize, const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const CharacterMovement& movement, const glm::ivec2& gridLoc, int playerID) const
{
	std::shared_ptr<GameObject> qbert = std::make_shared<GameObject>();
	qbert->SetTag("QBert");
	qbert = std::make_shared<GameObject>();

	auto gridComp = std::make_shared <GridComponent>(qbert, gridSize, blockSize, gridLoc, offset);
	qbert->AddComponent(gridComp);
	auto pos = gridComp->CalcGridPos();
	pos += posFix;
	qbert->AddComponent(std::make_shared <TextureComponent>(qbert, "tempQbert.png", pos));
	qbert->AddComponent(std::make_shared <RenderComponent>(qbert));
	if (playerID == 0)
	{
		const auto healthComp = std::make_shared<HealthComponent>(qbert, 3);
		qbert->AddComponent(healthComp);
		gridComp->AddHealthComp(healthComp);
		const auto scoreComp = std::make_shared<ScoreComponent>(qbert);
		qbert->AddComponent(scoreComp);
		gridComp->AddScoreComp(scoreComp);
	}
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

std::shared_ptr<GameObject> QBertGameApplication::CreateCoily(Scene& scene, const glm::vec2& gridSize,
	const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const glm::ivec2& gridLoc) const
{
	if (!m_pQBert1)
		return nullptr;
	std::shared_ptr<GameObject> coily = std::make_shared<GameObject>();
	coily->SetTag("Coily");


	auto gridComp = std::make_shared <GridComponent>(coily, gridSize, blockSize, gridLoc, offset);
	coily->AddComponent(gridComp);
	auto pos = gridComp->CalcGridPos();
	pos += posFix;
	coily->AddComponent(std::make_shared <TextureComponent>(coily, "CoilyBall.png", pos));
	coily->AddComponent(std::make_shared <RenderComponent>(coily));
	
	auto qbertGridComp = m_pQBert1->GetComponent<GridComponent>();
	auto posFixActive = posFix;
	posFixActive.y -= 23;
	coily->AddComponent(std::make_shared <CoilyMoveComponent>(coily,1.f,posFix,posFixActive,m_pQBert1, "CoilyBall.png","CoilySnake.png",false));
	coily->AddComponent(std::make_shared <ObserverComponent>(coily, std::make_shared<QbertHealthObserver>()));
	coily->AddComponent(std::make_shared<SubjectComponent>(coily));
	const auto healthComp = std::make_shared<HealthComponent>(coily, 1);
	
	coily->AddComponent(healthComp);
	gridComp->AddHealthComp(healthComp);
	scene.Add(coily);
	return coily;
}

std::shared_ptr<GameObject> QBertGameApplication::CreateCoily(Scene& scene, const glm::vec2& gridSize,
	const glm::vec2& blockSize, const glm::vec3& posFix, const glm::vec2& offset, const CharacterMovement& movement,
	const glm::ivec2& gridLoc) const
{

	if (!m_pQBert1)
		return nullptr;
	std::shared_ptr<GameObject> coily = std::make_shared<GameObject>();
	coily->SetTag("Coily");


	auto gridComp = std::make_shared <GridComponent>(coily, gridSize, blockSize, gridLoc, offset);
	coily->AddComponent(gridComp);
	auto pos = gridComp->CalcGridPos();
	pos += posFix;
	coily->AddComponent(std::make_shared <TextureComponent>(coily, "CoilyBall.png", pos));
	coily->AddComponent(std::make_shared <RenderComponent>(coily));

	auto qbertGridComp = m_pQBert1->GetComponent<GridComponent>();
	auto posFixActive = posFix;
	posFixActive.y -= 23;
	coily->AddComponent(std::make_shared <CoilyMoveComponent>(coily, 1.f, posFix, posFixActive, m_pQBert1, "CoilyBall.png", "CoilySnake.png",true));
	coily->AddComponent(std::make_shared <ObserverComponent>(coily, std::make_shared<QbertHealthObserver>()));
	const auto healthComp = std::make_shared<HealthComponent>(coily, 3);
	coily->AddComponent( std::make_shared<SubjectComponent>(coily));
	coily->AddComponent(healthComp);
	gridComp->AddHealthComp(healthComp);
	scene.Add(coily);
	InputManager::GetInstance().AddCommand(movement.LeftDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily,glm::ivec3{ 0,1,0 },posFixActive));
	InputManager::GetInstance().AddCommand(movement.RightDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ 1,1,0 }, posFixActive));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ -1,-1,0 },posFixActive));
	InputManager::GetInstance().AddCommand(movement.RightUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ 0,-1,0 }, posFixActive));

	InputManager::GetInstance().AddCommand(movement.RightUpGamepad, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ 0,-1,0 },posFixActive));
	InputManager::GetInstance().AddCommand(movement.LeftDownGamepad, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ 0,1,0 },posFixActive));
	InputManager::GetInstance().AddCommand(movement.RightDownGamepad, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ 1,1,0 },posFixActive));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyGamepad, ExecuteType::Pressed, std::make_shared<MoveCoily>(coily, glm::ivec3{ -1,-1,0 },posFixActive));
	return coily;
}
