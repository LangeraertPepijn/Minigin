#include "MiniginPCH.h"
#include "HudObject.h"
#include "HudRenderComponent.h"

HudObject::HudObject( )


{
 
}

HudObject::~HudObject()
{
}


const std::vector<std::shared_ptr<HudBaseComponent>>& HudObject::GetComponents() const
{
	return m_Components;
}

std::shared_ptr<HudBaseComponent> HudObject::AddComponent(std::shared_ptr<HudBaseComponent> newComponent)
{
	m_Components.push_back(newComponent);
	return newComponent;
}

void HudObject::Update(float deltaTime)
{
	for (auto component : m_Components)
    {
        if(component->m_NeedsUpdate)
        {
			component->Update(deltaTime);
        }
    }
}
void HudObject::Render()
{
	for (auto component : m_Components)
	{
		auto temp = std::dynamic_pointer_cast<HudRenderComponent>(component);
		if (temp != nullptr)
		{
			temp->Render();
			break;
		}
	}
}