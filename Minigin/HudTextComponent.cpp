#include "MiniginPCH.h"
#include "HudTextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "HudObject.h"
#include "TransformComponent.h"

void HudTextComponent::Update(float deltaTime)
{
	deltaTime;
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { m_Color.x,m_Color.y ,m_Color.z }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), (m_PreFix + m_Text).c_str(), color);
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

void HudTextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void HudTextComponent::SetColor(const glm::tvec3<uint8_t> color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

std::shared_ptr<Texture2D> HudTextComponent::GetTexture()const
{
	return m_Texture;
}

void HudTextComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

void HudTextComponent::Render() const
{
	//auto temp = m_pParent.lock()->GetComponent<TransformComponent>();
	if (m_TransformComponent != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_TransformComponent->GetTransform().x, m_TransformComponent->GetTransform().y);
		return;
	}
	Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
}

HudTextComponent::HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text,
	const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color, const glm::vec3 position,
	const std::string& prefix)
	: HudBaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ Color }
	, m_TransformComponent(std::make_shared<HudTransformComponent>(parent, position))
	, m_PreFix(prefix)
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

HudTextComponent::HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color, const glm::vec3 position)
	: HudBaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ Color }
	, m_TransformComponent(std::make_shared<HudTransformComponent>(parent, position))
	, m_PreFix()
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


HudTextComponent::HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font)
	: HudBaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ 255,255,255 }
	, m_TransformComponent(std::make_shared<HudTransformComponent>(parent, glm::vec3{}))
	, m_PreFix()
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

HudTextComponent::HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color)
	: HudBaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ Color }
	, m_TransformComponent(std::make_shared<HudTransformComponent>(parent, glm::vec3{}))
	, m_PreFix()
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

HudTextComponent::HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::vec3 position)
	: HudBaseComponent(parent)
	, m_Font{ font }
	, m_Text{ text }
	, m_Texture{}
	, m_Color{ 255,255,255 }
	, m_TransformComponent(std::make_shared<HudTransformComponent>(parent, position))
	, m_PreFix()

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




