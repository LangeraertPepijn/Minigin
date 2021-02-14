#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "RenderComponent.h"

const std::vector<std::shared_ptr<dae::BaseComponent>>& dae::GameObject::GetComponents()
{
	return m_Components;
}

std::shared_ptr<dae::BaseComponent> dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> newComponent)
{
	m_Components.push_back(newComponent);
	return newComponent;
}

dae::GameObject::~GameObject()
{
	m_Components.clear();
}




//void dae::GameObject::Render() const
//{
//	const auto pos = m_Transform.GetPosition();
//	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
//}

void dae::GameObject::Update(float deltaTime)
{
	for (auto components : m_Components)
	{
		if(components->m_NeedsUpdate)
		{
			components->Update(deltaTime);
		}
	}
}
void dae::GameObject::Render()
{
	for (auto component : m_Components)
	{
		auto temp = std::dynamic_pointer_cast<RenderComponent>(component);
		if (temp != nullptr)
		{
			temp->Render();
		}
	}
}

