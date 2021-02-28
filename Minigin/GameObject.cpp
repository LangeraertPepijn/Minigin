#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Subject.h"
#include "RenderComponent.h"

void dae::GameObject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_ActorChanged->AddObserver( observer);
}

void dae::GameObject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_ActorChanged->RemoveObserver( observer);
}

const std::shared_ptr<dae::Subject> dae::GameObject::GetSubject()
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

