#include "MiniginPCH.h"
#include "RenderComponent.h"

dae::BaseComponent::BaseComponent()
	: m_pParent{nullptr}
	, m_NeedsRender{}
	, m_NeedsUpdate{}
{
}

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> parent)
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

void dae::BaseComponent::SetParent(std::shared_ptr<GameObject> parent)
{
	m_pParent = parent;
}
