#include "MiniginPCH.h"
#include "HudBaseComponent.h"
#include "HudObject.h"
dae::HudBaseComponent::HudBaseComponent(std::weak_ptr<HudObject> parent)
	: m_pParent{ parent }
	, m_NeedsRender{}
	, m_NeedsUpdate{}
{

}

void dae::HudBaseComponent::Update(float)
{

}

void dae::HudBaseComponent::Render() const
{
}

void dae::HudBaseComponent::SetParent(std::weak_ptr<HudObject> parent)
{
	m_pParent = parent;
}