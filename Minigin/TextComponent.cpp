#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "HudTextComponent.h"
#include "TransformComponent.h"

void dae::TextComponent::Update(float deltaTime)
{
	deltaTime;
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { m_Color.x,m_Color.y ,m_Color.z  }; // only white text is supported now
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
	if(m_HudText)
		m_HudText->SetText (m_Text);

}
void dae::TextComponent::SetColor(const glm::tvec3<uint8_t> color)
{
	m_Color = color;
	m_NeedsUpdate = true;
	if(m_HudText)
		m_HudText->SetColor (m_Color);
}

std::shared_ptr<dae::Texture2D> dae::TextComponent::GetTexture()const
{
	return m_Texture;
}

void dae::TextComponent::Render() const
{

	if (m_TransformComponent != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformComponent->GetTransform().x, m_TransformComponent->GetTransform().y);
		return;
	}
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}

dae::TextComponent::TextComponent(std::weak_ptr<GameObject> parent, const std::string& text,const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color, const glm::vec3 position)
	: BaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ Color }
    , m_TransformComponent(std::make_shared<TransformComponent>(parent,position))
{
	m_NeedsRender = true;
	const SDL_Color color = { m_Color.x,m_Color.y,m_Color.z }; // only white text is supported now
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


dae::TextComponent::TextComponent(std::weak_ptr<GameObject> parent, const std::string& text, const std::shared_ptr<Font>& font)
	: BaseComponent(parent)
	, m_Font {font}
	, m_Text{text}
	, m_Texture{}
	, m_Color{ 255,255,255 }
	, m_TransformComponent(std::make_shared<TransformComponent>(parent, glm::vec3{}))
{
	m_NeedsRender = true;
		const SDL_Color color = { m_Color.x,m_Color.y,m_Color.z }; // only white text is supported now
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

void dae::TextComponent::SetHudElement(const std::shared_ptr<HudTextComponent>& hud)
{
	m_HudText = hud;
}

dae::TextComponent::TextComponent(std::weak_ptr<GameObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color)
	: BaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{Color}
	, m_TransformComponent(std::make_shared<TransformComponent>(parent, glm::vec3{}))
{
	m_NeedsRender = true;
	const SDL_Color color = { Color.x,Color.y  ,Color.z }; // only white text is supported now
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

dae::TextComponent::TextComponent(std::weak_ptr<GameObject> parent, const std::string& text,const std::shared_ptr<Font>& font, const glm::vec3 position)
	: BaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ 255,255,255 }
	, m_TransformComponent(std::make_shared<TransformComponent>(parent, position))

{
	m_NeedsRender = true;
	const SDL_Color color = { m_Color.x,m_Color.y,m_Color.z }; // only white text is supported now
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




