#include "MiniginPCH.h"
#include "RenderComponent.h"



dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> parent)
	: m_pParent{parent}
	, m_NeedsRender{}
	, m_NeedsUpdate{}
{

}

void dae::BaseComponent::Update(float deltaTime)
{
	deltaTime;
}

void dae::BaseComponent::Render() const
{
}

void dae::BaseComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}
