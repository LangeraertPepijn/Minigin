#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include"GameObject.h"
#include"TransformComponent.h"

void TextureComponent::Update(float)
{
}

void TextureComponent::SetTexture(const std::string& texture)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}

void TextureComponent::SetPosition(const glm::vec3& trans)
{
    m_TransformComponent->SetTransform(trans);
}

void TextureComponent::Translate(const glm::vec3& trans)
{
    m_TransformComponent->AddTransform(trans);
}


std::shared_ptr<Texture2D> TextureComponent::GetTexture()const
{
    return m_Texture;
}

void TextureComponent::Render() const
{
    auto temp = m_pParent.lock()->GetComponent<TransformComponent>();
    if (temp != nullptr)
    {
	    Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformComponent->GetTransform().x, m_TransformComponent->GetTransform().y);
        return;
    }
    Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}

TextureComponent::TextureComponent(std::weak_ptr<GameObject> parent, const std::string& texture,const glm::vec3 position)
	:BaseComponent(parent)
	, m_Texture{}
	, m_TransformComponent(std::make_shared<TransformComponent>(parent,position))
{
    m_NeedsRender = true;
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}

TextureComponent::TextureComponent(std::weak_ptr<GameObject> parent, const std::string& texture)
    : BaseComponent(parent)
    , m_Texture{}
	,  m_TransformComponent(std::make_shared<TransformComponent>(parent,glm::vec3{}))
    
{
    m_NeedsRender = true;
    m_Texture = ResourceManager::GetInstance().LoadTexture(texture);
}
