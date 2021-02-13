#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransformComponent.h"

void dae::TextComponent::Update(float deltaTime)
{
	deltaTime;
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

std::shared_ptr<dae::Texture2D> dae::TextComponent::GetTexture()
{
	return m_Texture;
}

void dae::TextComponent::Render() const
{
	auto temp = m_pParent->GetComponent<TransformComponent>();
	if (temp != nullptr)
	{
		const auto pos = m_pParent->GetComponent<TransformComponent>()->GetTransform();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		return;
	}
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}



dae::TextComponent::TextComponent(std::shared_ptr<GameObject> parent, const std::string& text, const std::shared_ptr<Font>& font)
	: BaseComponent(parent)
	, m_Font {font}
	, m_Text{text}
	, m_Texture{}
{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		
}




