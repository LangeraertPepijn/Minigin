#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(std::shared_ptr<GameObject> parent, std::shared_ptr<Texture2D> texture )
	: BaseComponent(parent)

{

	m_Texture = texture;
}

//void dae::RenderComponent::Update(float deltaTime)
//{
//	deltaTime;
//}

void dae::RenderComponent::Render()const
{
	m_pParent->
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}


