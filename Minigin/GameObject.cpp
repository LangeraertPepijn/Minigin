#include "MiniginPCH.h"
#pragma once
#include "GameObject.h"

#include "RenderComponent.h"
#include "TransformComponent.h"

const std::vector<std::shared_ptr<BaseComponent>>& GameObject::GetComponents()const
{
	return m_Components;
}

std::shared_ptr<BaseComponent> GameObject::AddComponent(std::shared_ptr<BaseComponent> newComponent)
{
	m_Components.push_back(newComponent);
	return newComponent;
}

GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>(weak_from_this(), glm::vec3{0,0,0}));
}

GameObject::GameObject(const glm::vec3& pos)
{
	AddComponent(std::make_shared<TransformComponent>(weak_from_this(), pos));
}

GameObject::~GameObject()
{
	m_Components.clear();
}

GameObject::GameObject(const GameObject& other)
{
	m_Components = other.m_Components;
	m_ActorChanged = other.m_ActorChanged;
}




void GameObject::Update(float deltaTime)
{
	for (auto components : m_Components)
	{
		if(components->m_NeedsUpdate)
		{
			components->Update(deltaTime);
		}
	}
}
void GameObject::Render()
{
	for (auto component : m_Components)
	{
		auto temp = std::dynamic_pointer_cast<RenderComponent>(component);
		if (temp != nullptr)
		{
			temp->Render();
			break;
		}
	}
}

void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

std::string GameObject::GetTag() const
{
	return  m_Tag;
}

