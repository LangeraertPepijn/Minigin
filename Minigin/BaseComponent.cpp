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
{

}

void dae::BaseComponent::SetParent(std::shared_ptr<GameObject> parent)
{
	m_pParent = parent;
}
