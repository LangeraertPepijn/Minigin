#pragma once
#include "HudBaseComponent.h"
#include "HudTransformComponent.h"
namespace dae
{

	class Font;
	class Texture2D;
	class HudTextComponent final : public HudBaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;


		void SetText(const std::string& text);
		void SetColor(const glm::tvec3<uint8_t> color);
		std::shared_ptr<Texture2D> GetTexture()const;
		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		virtual void Render()const override;

		HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color, const glm::vec3 position,const std::string& prefix);
		HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color, const glm::vec3 position);
		HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::tvec3<uint8_t>& Color);
		HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font, const glm::vec3 position);
		HudTextComponent(std::weak_ptr<HudObject> parent, const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~HudTextComponent() = default;
		HudTextComponent(const HudTextComponent& other) = delete;
		HudTextComponent(HudTextComponent&& other) = delete;
		HudTextComponent& operator=(const HudTextComponent& other) = delete;
		HudTextComponent& operator=(HudTextComponent&& other) = delete;
	private:

		glm::tvec3<uint8_t> m_Color;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<HudTransformComponent> m_TransformComponent;
		std::string m_PreFix;
	};

}
