#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
namespace dae
{

	class Font;
	class Texture2D;
	class HudTextComponent;
	class TextComponent final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		//virtual void Render()  override;

		void SetText(const std::string& text);
		void SetColor(const glm::tvec3<uint8_t> color);
		std::shared_ptr<Texture2D> GetTexture()const;
		virtual void Render()const override;

		TextComponent(std::weak_ptr<GameObject> parent,const std::string& text, const std::shared_ptr<Font>& font,const glm::tvec3<uint8_t>& Color, const glm::vec3 position);
		TextComponent(std::weak_ptr<GameObject> parent,const std::string& text, const std::shared_ptr<Font>& font,const glm::tvec3<uint8_t>& Color);
		TextComponent(std::weak_ptr<GameObject> parent,const std::string& text, const std::shared_ptr<Font>& font, const glm::vec3 position);
		TextComponent(std::weak_ptr<GameObject> parent,const std::string& text, const std::shared_ptr<Font>& font);
		void SetHudElement(const std::shared_ptr<HudTextComponent>& hud);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:

		glm::tvec3<uint8_t> m_Color;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<TransformComponent> m_TransformComponent;
		std::shared_ptr<HudTextComponent> m_HudText;
	};

}
