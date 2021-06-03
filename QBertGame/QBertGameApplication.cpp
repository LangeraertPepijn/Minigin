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
#include "QbertMovement.h"
void QBertGameApplication::UserLoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("QbertScene");
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared <TextureComponent>(go, "background.jpg"));
	go->AddComponent(std::make_shared <RenderComponent>(go));
	scene.Add(go);
	CreateBlocks(scene);
	CreateQBert(scene,QBertMovement{},glm::ivec2{0,6});
	QBertMovement movement{ SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A,SDL_SCANCODE_W };
	CreateQBert(scene,movement,glm::ivec2{6,6});


}

void QBertGameApplication::UserCleanUp()
{
}

void QBertGameApplication::UserUpdate(float)
{

}

void QBertGameApplication::CreateBlocks(Scene& scene)const
{


	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	int locationCounter = 0;
	BlockManager::GetInstance().SetActiveTex("Cube2.png");
	BlockManager::GetInstance().SetInActiveTex("Cube1.png");
	BlockManager::GetInstance().SetCanRevert(true);
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i % 2 == 1)
			{

				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(m_Offset.x + (j - i / 2) * m_BlockSize.x - m_BlockSize.x / 2, m_Offset.y + i * m_BlockSize.y, 0);
				auto texComp = std::make_shared <TextureComponent>(go, "Cube1.png", pos);
				go->AddComponent(texComp);
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go, m_GridSize,m_BlockSize,glm::ivec2{j,i},m_Offset));
				BlockManager::GetInstance().AddBlock(int(j*m_GridSize.x+i),texComp);
				scene.Add(go);
			}
			else
			{
				go = std::make_shared<GameObject>();
				auto pos = glm::vec3(m_Offset.x + (j - i / 2) * m_BlockSize.x , m_Offset.y + i * m_BlockSize.y, 0);
				auto texComp = std::make_shared <TextureComponent>(go, "Cube1.png", pos);
				go->AddComponent(texComp);
				go->AddComponent(std::make_shared <RenderComponent>(go));
				go->AddComponent(std::make_shared <GridComponent>(go, glm::ivec2{ 7,7 }, m_BlockSize, glm::ivec2{ j,i }, m_Offset));
				BlockManager::GetInstance().AddBlock(int(j*m_GridSize.x+i),texComp);
				scene.Add(go);
			}
			locationCounter++;
		}
	}
}

std::shared_ptr<GameObject> QBertGameApplication::CreateQBert(Scene& scene, const QBertMovement& movement, const glm::ivec2& gridLoc) const
{
	std::shared_ptr<GameObject> qbert = std::make_shared<GameObject>();
	qbert = std::make_shared<GameObject>();

	auto gridComp = std::make_shared <GridComponent>(qbert, m_GridSize, m_BlockSize, gridLoc, m_Offset);
	qbert->AddComponent(gridComp);
	auto pos = gridComp->CalcGridPos();
	pos += m_PosFix;
	qbert->AddComponent(std::make_shared <TextureComponent>(qbert, "tempQbert.png", pos));
	qbert->AddComponent(std::make_shared <RenderComponent>(qbert));
	scene.Add(qbert);



	InputManager::GetInstance().AddCommand(movement.LeftDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveLeftDown>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.RightDownKeyboard, ExecuteType::Pressed, std::make_shared<MoveRightDown>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveLeftUp>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.RightUpKeyboard, ExecuteType::Pressed, std::make_shared<MoveRightUp>(qbert, m_PosFix));

	InputManager::GetInstance().AddCommand(movement.RightUpGamepad, ExecuteType::Pressed, std::make_shared<MoveRightUp>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.LeftDownGamepad, ExecuteType::Pressed, std::make_shared<MoveLeftDown>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.RightDownGamepad, ExecuteType::Pressed, std::make_shared<MoveRightDown>(qbert, m_PosFix));
	InputManager::GetInstance().AddCommand(movement.LeftUpKeyGamepad, ExecuteType::Pressed, std::make_shared<MoveLeftUp>(qbert, m_PosFix));

	return qbert;
}
