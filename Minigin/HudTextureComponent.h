#pragma once
#include "HudTransformComponent.h"
#include "HudBaseComponent.h"


class Font;
class Texture2D;
class HudTextureComponent final : public HudBaseComponent
{
public:
	virtual void Update(float);


	void SetTexture(const std::string& texture);
	std::shared_ptr<Texture2D> GetTexture()const;
	virtual void Render()const override;

	HudTextureComponent(std::weak_ptr<HudObject> parent, const std::string& texture, const glm::vec3 position);
	HudTextureComponent(std::weak_ptr<HudObject> parent, const std::string& texture);
	virtual ~HudTextureComponent() = default;
	HudTextureComponent(const HudTextureComponent& other) = delete;
	HudTextureComponent(HudTextureComponent&& other) = delete;
	HudTextureComponent& operator=(const HudTextureComponent& other) = delete;
	HudTextureComponent& operator=(HudTextureComponent&& other) = delete;
private:
	std::shared_ptr<Texture2D> m_Texture;
	std::shared_ptr<HudTransformComponent> m_TransformComponent;
};



