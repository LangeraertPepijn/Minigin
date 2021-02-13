#pragma once
#include "BaseComponent.h"
namespace dae
{

	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		//virtual void Render()  override;

		void SetText(const std::string& text);
		std::shared_ptr<Texture2D> GetTexture();
		virtual void Render()const override;

		TextComponent(std::shared_ptr<GameObject> parent,const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:

		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};

}