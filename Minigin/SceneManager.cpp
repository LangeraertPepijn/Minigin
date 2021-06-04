#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
void SceneManager::Update(float deltaTime)
{
	if(m_ActiveScene)
		m_ActiveScene->Update(deltaTime);
	//for(auto& scene : m_Scenes)
	//{
	//	scene->Update(deltaTime);
	//}
}

void SceneManager::Render()
{
	if(m_ActiveScene)
		m_ActiveScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveScene = scene;
	return *scene;
}

void SceneManager::SetActiveScene(std::shared_ptr<Scene> scene)
{
	m_ActiveScene = scene;
}

std::shared_ptr<Scene> SceneManager::GetAcitveScene() const
{
	return m_ActiveScene;
}

void SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
	std::_Erase_remove_if(m_Scenes, [scene](std::shared_ptr<Scene>OtherScene) {return scene == OtherScene; });
	if (m_ActiveScene == scene)
		m_ActiveScene = nullptr;
}






