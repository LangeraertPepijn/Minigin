#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

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

void SceneManager::SetActiveScene(int index)
{
	if (index < 0)
		return;
	if (index < m_Scenes.size())
		m_ActiveScene = m_Scenes[index];
	else
		m_ActiveScene = m_Scenes[index% m_Scenes.size()];

}

int SceneManager::GetActiveSceneIndex()
{
	int i = -1;
	const auto scene = std::find_if(m_Scenes.begin(), m_Scenes.end(),  [this,i](std::shared_ptr<Scene> scene)mutable
		{
			i++;
			return (m_ActiveScene==scene);

		});
	if (scene == m_Scenes.end())
		return -1;
	return i;
}
