#include "MiniginPCH.h"
#include "HudBaseComponent.h"
#include "HudObject.h"
HudBaseComponent::HudBaseComponent(std::weak_ptr<HudObject> parent)
	: m_pParent{ parent }
	, m_NeedsRender{}
	, m_NeedsUpdate{}
{

}

void HudBaseComponent::Update(float)
{

}

void HudBaseComponent::Render() const
{
}

void HudBaseComponent::SetParent(std::weak_ptr<HudObject> parent)
{
	m_pParent = parent;
}