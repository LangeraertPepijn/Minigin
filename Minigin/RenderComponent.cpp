#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent(std::weak_ptr<GameObject> parent )
	: BaseComponent(parent)

{


}

//void RenderComponent::Update(float deltaTime)
//{
//	deltaTime;
//}

void RenderComponent::Update(float)
{
}

void RenderComponent::Render()const
{
	for (const std::shared_ptr<BaseComponent> component : m_pParent.lock()->GetComponents())
	{
		if (component->m_NeedsRender)
		{
			component->Render();
		}
	}
}




