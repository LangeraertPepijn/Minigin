#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(std::shared_ptr<GameObject> parent )
	: BaseComponent(parent)

{


}

//void dae::RenderComponent::Update(float deltaTime)
//{
//	deltaTime;
//}

void dae::RenderComponent::Render()const
{
	for (BaseComponent* component : m_pParent->GetComponents())
	{
		if (component->m_NeedsRender)
		{
			component->Render();
		}
	}
}




