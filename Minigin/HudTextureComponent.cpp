#include "MiniginPCH.h"
#include "HudTextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include"HudObject.h"


void HudTextureComponent::Update(float)
{
}

void HudTextureComponent::SetTexture(const std::string& texture)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}

std::shared_ptr<Texture2D> HudTextureComponent::GetTexture()const
{
    return m_Texture;
}

void HudTextureComponent::Render() const
{
    auto temp = m_pParent.lock()->GetComponent<TransformComponent>();
    if (temp != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformComponent->GetTransform().x, m_TransformComponent->GetTransform().y);
        return;
    }
    Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}

HudTextureComponent::HudTextureComponent(std::weak_ptr<HudObject> parent, const std::string& texture, const glm::vec3 position)
    :HudBaseComponent(parent)
    , m_Texture{}
    , m_TransformComponent(std::make_shared<HudTransformComponent>(parent, position))
{
    m_NeedsRender = true;
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}

HudTextureComponent::HudTextureComponent(std::weak_ptr<HudObject> parent, const std::string& texture)
    : HudBaseComponent(parent)
    , m_Texture{}
    , m_TransformComponent(std::make_shared<HudTransformComponent>(parent, glm::vec3{}))

{
    m_NeedsRender = true;
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}
