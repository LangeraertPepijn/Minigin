#pragma once
#include "BaseComponent.h"
namespace dae
{

	class Font;
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		virtual void Update(float );
		//virtual void Render()  override;

		void SetTexture(const std::string& texture);
		std::shared_ptr<Texture2D> GetTexture()const;
		virtual void Render()const override;

		TextureComponent(std::weak_ptr<GameObject> parent, const std::string& texture);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_Texture;
	};

}
