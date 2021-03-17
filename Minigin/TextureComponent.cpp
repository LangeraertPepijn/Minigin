#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include"GameObject.h"
#include"TransformComponent.h"

void dae::TextureComponent::Update(float)
{
}

void dae::TextureComponent::SetTexture(const std::string& texture)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()const
{
    return m_Texture;
}

void dae::TextureComponent::Render() const
{
    auto temp = m_pParent.lock()->GetComponent<TransformComponent>();
    if (temp != nullptr)
    {
        const auto pos = m_pParent.lock()->GetComponent<TransformComponent>()->GetTransform();
        dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
        return;
    }
    dae::Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}

dae::TextureComponent::TextureComponent(std::weak_ptr<GameObject> parent, const std::string& texture)
    : BaseComponent(parent)
    , m_Texture{}
    
{
    m_NeedsRender = true;
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}
