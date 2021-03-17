#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> parent )
	: BaseComponent(parent)

{


}

//void dae::RenderComponent::Update(float deltaTime)
//{
//	deltaTime;
//}

void dae::RenderComponent::Update(float)
{
}

void dae::RenderComponent::Render()const
{
	for (const std::shared_ptr<BaseComponent> component : m_pParent.lock()->GetComponents())
	{
		if (component->m_NeedsRender)
		{
			component->Render();
		}
	}
}




