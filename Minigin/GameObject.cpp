#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "RenderComponent.h"

dae::BaseComponent* dae::GameObject::AddComponent(BaseComponent* newComponent)
{
	m_Components.push_back(newComponent);
	return newComponent;
}

dae::GameObject::~GameObject() = default;



//void dae::GameObject::Render() const
//{
//	const auto pos = m_Transform.GetPosition();
//	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
//}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
void dae::GameObject::Update(float deltaTime)
{
	float i = deltaTime;
	i++;
}
void dae::GameObject::Render()
{
	for (auto component : m_Components)
	{
		auto temp = dynamic_cast<RenderComponent*>(component);
		if (temp != nullptr)
		{
			temp->Render();
		}
	}
}

