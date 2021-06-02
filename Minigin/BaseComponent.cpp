#include "MiniginPCH.h"
#include "RenderComponent.h"



BaseComponent::BaseComponent(std::weak_ptr<GameObject> parent)
	: m_pParent{parent}
	, m_NeedsRender{}
	, m_NeedsUpdate{}
{

}

void BaseComponent::Update(float )
{

}

void BaseComponent::Render() const
{
}

void BaseComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}
