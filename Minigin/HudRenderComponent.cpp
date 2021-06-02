#include "MiniginPCH.h"
#include "HudRenderComponent.h"
#include  "HudObject.h"
HudRenderComponent::HudRenderComponent(std::weak_ptr<HudObject> parent)
	: HudBaseComponent(parent)

{


}


void HudRenderComponent::Update(float)
{
}

void HudRenderComponent::Render()const
{
	for (const std::shared_ptr<HudBaseComponent> component : m_pParent.lock()->GetComponents())
	{
		if (component->m_NeedsRender)
		{
			component->Render();
		}
	}
}