#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Subject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"



 std::shared_ptr<dae::Subject> dae::GameObject::GetSubject()const
{
	return  m_ActorChanged;
}

void dae::GameObject::SetSubject(std::shared_ptr<Subject> subject)
{
	m_ActorChanged = subject;
}

const std::vector<std::shared_ptr<dae::BaseComponent>>& dae::GameObject::GetComponents()const
{
	return m_Components;
}

std::shared_ptr<dae::BaseComponent> dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> newComponent)
{
	m_Components.push_back(newComponent);
	return newComponent;
}

dae::GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>(weak_from_this(), glm::vec3{0,0,0}));
}

dae::GameObject::GameObject(const glm::vec3& pos)
{
	AddComponent(std::make_shared<TransformComponent>(weak_from_this(), pos));
}

dae::GameObject::~GameObject()
{
	m_Components.clear();
}

dae::GameObject::GameObject(const GameObject& other)
{
	m_Components = other.m_Components;
	m_ActorChanged = other.m_ActorChanged;
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

